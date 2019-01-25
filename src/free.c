/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:29:34 by lportay           #+#    #+#             */
/*   Updated: 2019/01/25 18:55:00 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** DEFRAGMENTATION SCHEME
**
** |== X ==| -> free block
** |xxxxxxx| -> busy block
**
** |== prev ==| |== p ==| |== next ==| -> |=========== prev =============|
**
** |= prev =| |xxx| |= p =| |= next =| -> |= prev =| |xxx| |===== p =====|
**
** |= prev =| |= p =| |xxx| |= next =| -> |=== prev ====| |xxx| |= next =|
*/

static int	defragment_next(t_mem *prev, t_mem *p, t_mem *next)
{
	t_mem *n;

	add_len(p, get_len(next));
	set_prev(p, prev);
	n = get_next(next);
	set_next(p, n);
	if (n)
		set_prev(n, p);
	return (1);
}

int			soft_defragment(t_mem *prev, t_mem *p, t_mem *next)
{
	t_mem *n;

	if (prev != NULL && adj_mem(prev, p))
	{
		if (adj_mem(p, next))
		{
			add_len(prev, get_len(p) + get_len(next));
			n = get_next(next);
			set_next(prev, n);
			if (n)
				set_prev(n, prev);
			return (1);
		}
		add_len(prev, get_len(p));
		return (1);
	}
	else if (adj_mem(p, next))
		return (defragment_next(prev, p, next));
	return (0);
}

static void	handle_end_block(t_mem *m, t_mem *p)
{
	t_mem *iter;

	while ((iter = get_next(m)) != NULL)
		m = iter;
	if (adj_mem(m, p))
		add_len(m, get_len(p));
	else
	{
		set_next(m, p);
		set_prev(p, m);
		set_next(p, NULL);
	}
}

void	release_mem(t_mem **mem, t_mem *p)
{
	t_mem	*m;
	t_mem	*prev;

	m = *mem;
	while (m && p > m)
		m = get_next(m);
	if (!m)
		return (handle_end_block(*mem, p));

	prev = get_prev(m);

	if (soft_defragment(prev, p, m) == 0)
	{
		if (prev)
			set_next(prev, p);
		set_prev(p, prev);
		set_prev(m, p);
		set_next(p, m);
	}
	if (p < *mem)
		*mem = p;
}

void	release_large(t_mem **mem, t_mem *p)
{
	if (get_len(p) > LARGE_THRESHOLD)
		munmap(p, get_len(p));
	else
	{
		if (*mem == NULL)
			set_next(p, NULL);
		else
		{
			set_next(p, *mem);
			set_prev(*mem, p);
		}
			set_prev(p, NULL);
			*mem = p;
	}
}

void	free(void *ptr)
{
	size_t l;

	if (!ptr)
		return ;
	ptr -= sizeof(size_t);

	if (getenv("MallocTrackMemory"))
		pop_alloc(&g_m.tracked, ptr);

	l = get_len(ptr);
	if (l <= TINY)
		release_mem(&g_m.tiny, ptr);
	else if (l <= SMALL)
		release_mem(&g_m.small, ptr);
	else
		release_large(&g_m.large, ptr);
}
