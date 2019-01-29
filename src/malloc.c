/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:00:57 by lportay           #+#    #+#             */
/*   Updated: 2019/01/29 14:52:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

struct s_mem	g_m;
pthread_mutex_t	g_lock;

static void	init_mem(t_mem *m)
{
	t_mem *c;

	set_len(m, TINY_LEN);
	set_prev(m, NULL);
	set_next(m, m + TINY_LEN);

	c = get_next(m);

	set_len(c, SMALL_LEN);
	set_prev(c, m);
	set_next(c, NULL);

	assert(c - m == TINY_LEN);//
	assert(get_len(c) == SMALL_LEN);//
}

static int		alloc_mem(void)
{
	g_m.pre_alloc = mmap(NULL, PRE_ALLOC_LEN, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (g_m.pre_alloc == MAP_FAILED)
	{
		g_m.pre_alloc = NULL;
		return (-1);
	}
	if (getenv("MallocTrackMemory"))
	{
		g_m.tracked = mmap(NULL, TRK_LEN, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		if (g_m.tracked == MAP_FAILED)
		{
			munmap(g_m.pre_alloc, PRE_ALLOC_LEN);
			g_m.pre_alloc = NULL;
			g_m.tracked = NULL;
			return (-1);
		}
		set_val(g_m.tracked, NULL);
	}
	else
		g_m.tracked = NULL;
	if (g_m.pre_alloc == MAP_FAILED)
		return (-1);
	g_m.tiny = g_m.pre_alloc;
	return (0);
}

void	*get_mem(t_mem **mem, size_t s)
{
	t_mem	*m;

	m = *mem;

	while (m && get_len(m) < s)
		m = get_next(m);
	if (!m)
		// defragmenter et relancer la recherche
		return (NULL);
	if (get_len(m) == s)
		cut(m);
	else
		shorten(m, s);

	if (m == *mem)
	{
		*mem = get_next(*mem);
		assert(*mem - m == (long)s);
	}
	return (m);
}

void	*malloc(size_t size)
{
	void	*r;

	//ca marche pas
	pthread_mutex_init(&g_lock, NULL);
	pthread_mutex_lock(&g_lock);
	sleep(3);
	if (g_m.pre_alloc == NULL)
	{
		if (alloc_mem() == -1)
			return (NULL);
		init_mem(g_m.tiny);
		g_m.small = get_next(g_m.tiny);
	}

	if (size < MIN_ALLOC)
		size = MIN_ALLOC;
	size += sizeof(size_t);

	if (size <= TINY)
		r = get_mem(&g_m.tiny, size);
	else if (size <= SMALL)
		r = get_mem(&g_m.small, size);
	else
		r = large_alloc(&g_m.large, size);

	if (getenv("MallocTrackMemory") && g_m.tracked)
		push_alloc(g_m.tracked, r);
	P(r);
	pthread_mutex_unlock(&g_lock);
	return (!r ? NULL : r + sizeof(size_t));
}

int main(void)
{
	pthread_t tid[2];

	pthread_create(&(tid[0]), NULL, (void *(*)(void *))&malloc, NULL);
	pthread_create(&(tid[1]), NULL, (void *(*)(void *))&malloc, NULL);
	pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
//	void *s = malloc(21);
//	P(s);
//	void *p = calloc(21, 42);
//	P(p);
//	void *r = realloc(s, 42);
//	P(r);
	//(void)r;
//	free(p);
}
