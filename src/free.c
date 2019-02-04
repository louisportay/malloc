/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:29:34 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 16:08:02 by lportay          ###   ########.fr       */
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

static void	nomem(t_mem **mem, t_mem *p)
{
	*mem = p;
	set_prev(p, NULL);
	set_next(p, NULL);
}

void		release_mem(t_mem **mem, t_mem *p)
{
	t_mem	*n;
	t_mem	*prev;

	if (!(*mem))
		return (nomem(mem, p));
	n = *mem;
	while (n && p > n)
		n = get_next(n);
	if (!n)
		return (handle_end_block(*mem, p));
	prev = get_prev(n);
	if (soft_defragment(prev, p, n) == 0)
	{
		if (prev)
			set_next(prev, p);
		set_prev(p, prev);
		set_prev(n, p);
		set_next(p, n);
	}
	if (p < *mem)
		*mem = p;
}

void		release_large(t_mem **mem, t_mem *p)
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

void		free(void *ptr)
{
	size_t l;

	if (!ptr || g_m.pre_alloc == NULL)
		return ;
	pthread_mutex_lock(&g_lock);
	if (check_alloc(ptr - HEADER_SIZE) == -1)
	{
		pthread_mutex_unlock(&g_lock);
		return ;
	}
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
