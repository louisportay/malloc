/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:29:34 by lportay           #+#    #+#             */
/*   Updated: 2019/02/01 10:25:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The allocated block is localized at the very end of the freelist
*/

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

	if (!ptr || g_m.pre_alloc == NULL || check_alloc(ptr - HEADER_SIZE) == -1)
		return ;
	pthread_mutex_lock(&g_lock);
	ptr -= HEADER_SIZE;
	pop_alloc(g_m.tracked, ptr);

	l = get_len(ptr);
	if (l <= TINY)
		release_mem(&g_m.tiny, ptr);
	else if (l <= SMALL)
		release_mem(&g_m.small, ptr);
	else
		release_large(&g_m.large, ptr);
	pthread_mutex_unlock(&g_lock);
}
