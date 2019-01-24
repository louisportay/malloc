/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:00:57 by lportay           #+#    #+#             */
/*   Updated: 2019/01/24 15:31:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

	assert(c - m == TINY_LEN);
	assert(get_len(c) == SMALL_LEN);
}

static int		alloc_mem(t_mem **m)
{
	*m = mmap(NULL, PRE_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (*m == MAP_FAILED)
		return (-1);
	return (0);
}

void	*get_mem(t_mem **mem, size_t s)
{
	t_mem	*m;

	m = *mem;
	if (s < MIN_ALLOC)
		s = MIN_ALLOC;
	else
		s += sizeof(size_t);

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

void	*_malloc(size_t size)
{
	static t_mem	*t_free;
	static t_mem	*s_free;
	static t_mem	*l_free;
	void			*r;

	if (t_free == NULL)
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
		r = large_alloc(&l_free, size);

	return (r + sizeof(size_t));
}

#include <string.h> //

int main(void)
{
	void *s = _malloc(SMALL + 1);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
//	 s = _malloc(16);
	DUMP_MEM(s);
//	void *q = _malloc(16);
//	DUMP_MEM(q);
	strcpy(s, "0123456789");
	printf("%s\n", s);
}
