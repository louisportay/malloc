/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:00:57 by lportay           #+#    #+#             */
/*   Updated: 2019/01/25 16:01:27 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

struct s_mem g_m;

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

void	*malloc(size_t size)
{
	void			*r;

	if (g_m.tiny == NULL)
	{
		if (alloc_mem(&g_m.tiny) == -1)
			return (NULL);
		init_mem(g_m.tiny);
		g_m.small = get_next(g_m.tiny);
	}
	if (size <= TINY)
		r = get_mem(&g_m.tiny, size);
	else if (size <= SMALL)
		r = get_mem(&g_m.small, size);
	else
		r = large_alloc(&g_m.large, size);
	return (r + sizeof(size_t));
}

#include <string.h> //

int main(void)
{
	void *s = malloc(16);
	DUMP_MEM(s);
	free(s);
	s = malloc(16);
	DUMP_MEM(s);
}
