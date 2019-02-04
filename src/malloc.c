/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:00:57 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 12:55:27 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

struct s_mem	g_m;
//pthread_mutex_t	g_lock = PTHREAD_MUTEX_INITIALIZER;

static void	init_mem(t_mem *m)
{
	t_mem *c;

	g_m.tiny = m;
	set_len(m, TINY_LEN);
	set_prev(m, NULL);
	set_next(m, NULL);

	c = m + TINY_LEN;

	g_m.small = c;
	set_len(c, SMALL_LEN);
	set_prev(c, NULL);
	set_next(c, NULL);

	assert(c - m == TINY_LEN);//
	assert(get_len(c) == SMALL_LEN);//
	assert(g_m.tiny == g_m.pre_alloc);//
	assert(g_m.tiny + TINY_LEN == g_m.small);//
}

static int		alloc_mem(void)
{
	g_m.pre_alloc = mmap(NULL, PRE_ALLOC_LEN, PROT, MAP, -1, 0);
	if (g_m.pre_alloc == MAP_FAILED)
	{
		g_m.pre_alloc = NULL;
		return (-1);
	}

	g_m.tracked = mmap(NULL, TRK_LEN, PROT, MAP, -1, 0);
	if (g_m.tracked == MAP_FAILED)
	{
		munmap(g_m.pre_alloc, PRE_ALLOC_LEN);
		g_m.pre_alloc = NULL;
		g_m.tracked = NULL;
		return (-1);
	}
	set_val(g_m.tracked, NULL);

	assert(g_m.pre_alloc != MAP_FAILED);//
	assert(g_m.large == NULL);//

	return (0);
}

static	int	init(void)
{
	if (alloc_mem() == -1)
	{
		//pthread_mutex_unlock(&g_lock);
		return (-1);
	}
	init_mem(g_m.pre_alloc);
	return (0);
}

void	*get_mem(t_mem **mem, size_t s)
{
	t_mem	*m;

	m = *mem;
	while (m && get_len(m) < s)
		m = get_next(m);
	if (!m)
		return (NULL);
	if (get_len(m) == s)
		cut(m);
	else
		shorten(m, s);

	if (m == *mem)
		*mem = get_next(*mem);
	return (m);
}

void	*malloc(size_t size)
{
	void	*r;

	//pthread_mutex_lock(&g_lock);

	if (g_m.pre_alloc == NULL && init() == -1)
		return (NULL);

	if (size < MIN_ALLOC)
		size = MIN_ALLOC;
	size = uround(size, 16);
	size += HEADER_SIZE;

	if (size <= TINY)
		r = get_mem(&g_m.tiny, size);
	else if (size <= SMALL)
		r = get_mem(&g_m.small, size);
	else
		r = large_alloc(&g_m.large, size);

	if (r)
		push_alloc(g_m.tracked, r);

	//pthread_mutex_unlock(&g_lock);

	return (!r ? NULL : r + HEADER_SIZE);
}

//int main(void)
//{
//}
