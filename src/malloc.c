/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:00:57 by lportay           #+#    #+#             */
/*   Updated: 2019/01/22 19:00:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	set_prev(t_mem *m, void *v)
{
	*(void **)(m + sizeof(void *)) = v;
}

t_mem	*get_prev(t_mem *m)
{
	return *(void **)(m + sizeof(void *));
}

void	set_next(t_mem *m, void *v)
{
	*(void **)(m + (sizeof(void *) << 1)) = v;
}

t_mem	*get_next(t_mem *m)
{	
	return *(void **)(m + (sizeof(void *) << 1));
}

void	set_len(t_mem *m, size_t len)
{
	*(size_t *)m = len;
}

size_t	get_len(t_mem *m)
{
	return *((size_t *)m);
}

void	init_mem(t_mem *m)
{
	t_mem *c;

	set_len(m, TINY_LEN);
	set_prev(m, NULL);
	set_next(m, m + TINY_LEN + 1);

	c = get_next(m);

	set_len(c, SMALL_LEN);
	set_prev(c, m);
	set_next(c, NULL);

	assert(c - m == TINY_LEN + 1);
	assert(get_len(c) == SMALL_LEN);
}

int		alloc_mem(t_mem **m)
{
	*m = mmap(NULL, PRE_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (*m == MAP_FAILED)
		return (-1);
	return (0);
}

void	shorten(t_mem *m, size_t rs)
{
	// sauver la len, le prev et le next
	// aller a l'offset rs + 1
	// set la len a len - rs
	// reset prev et next
}

void	cut(t_mem *m)
{
	//if prev
	//	prev->next = m->next
	//if next
	//	next->prev = m->prev
}

void	*get_mem(t_mem **mem, size_t s)
{
	t_mem *m;

	m = *mem;
	if (s < MIN_ALLOC)
		s = MIN_ALLOC;
	else
		s += sizeof(size_t);

	while (get_len(m) < s && m)
		m = get_next(m);	
	if (!m)
		return (NULL);
	if (get_len(m) == s)
		cut(m, s);

	if (m == *mem)
		*mem = get_next(*mem);
	
}

void	*_malloc(size_t size)
{
	(void)size;

	static t_mem	*t_free;
	static t_mem	*s_free;
	static t_mem	*l_free;
	void			*r;

	if (free == NULL)
	{
		if (alloc_mem(&t_free) == -1)
			return (NULL);
		init_mem(t_free);
		s_free = get_next(t_free);
	}
	if (size <= TINY)
		r = get_mem(&t_free, size);
	else if (size <= SMALL)
		r = get_mem(&s_free, size);
	else

	// look for 'size' or larger blocks in *free* list
		// if exact found
			// remove from free list and return it
			// put 'size' block in *alloced* list
		// if larger found
			// split, remove 'size' block from free list and return it
			// the other block is put back on the free list
			// put 'size' block in *alloced* list

	return (NULL);//
}

int main(void)
{
	_malloc(0);
}
