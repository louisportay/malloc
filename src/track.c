/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:55:15 by lportay           #+#    #+#             */
/*   Updated: 2019/02/01 10:33:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_mem	*last_alloc(t_mem *m)
{
	t_mem *a;

	while (get_val(a = next_alloc(m)) != NULL)
		m = a;
	return (m);
}

int		check_alloc(void *p)
{
	t_mem *iter;

	iter = g_m.tracked;
	while (iter != (g_m.tracked + TRK_LEN) && get_val(iter) != p)
		iter = next_alloc(iter);
	if (iter == g_m.tracked + TRK_LEN)
		return (-1);
	else if (get_val(iter) == p)
		return (0);
	return (-1);
}

/*
** |== Len ==| |== Value ==|
*/

void	push_alloc(t_mem *busy, t_mem *m)
{
	t_mem *iter;

	iter = busy;
	while (iter != (busy + TRK_LEN) && get_val(iter) != NULL)
		iter = next_alloc(iter);
	if (iter == busy + TRK_LEN)
	{
		write(STDERR_FILENO, "No space left to track memory allocation.\n",
				42);
		return ;
	}
	set_val(iter, m);
	set_len(iter, get_len(m));
	if (next_alloc(iter) != busy + TRK_LEN)
		set_val(next_alloc(iter), NULL);
}

void	pop_alloc(t_mem *busy, t_mem *m)
{
	t_mem *iter;
	t_mem *l;

	iter = busy;
	while (iter != (busy + TRK_LEN) && get_val(iter) != NULL && get_val(iter) != m)
		iter = next_alloc(iter);
	if (iter == (busy + TRK_LEN) || get_val(iter) == NULL)
		return ;
	l = last_alloc(iter);
	if (l != iter)
	{
		set_val(iter, get_val(l));
		set_len(iter, get_len(l));
	}
	set_val(l, NULL);
}

/*
** This is no algorithm project, so the bubbles will do the job
*/

static void	swap_mem(void *iter, void *next)
{
	void	*i;
	size_t	l;;

	i = get_val(iter);
	l = get_len(iter);
	set_val(iter, get_val(next));
	set_len(iter, get_len(next));
	set_val(next, i);
	set_len(next, l);
}

void	sort_alloc(t_mem *busy)
{
	int		sorted;
	t_mem	*iter;
	t_mem	*next;

	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		iter = busy;
		while (get_val(iter) && (next = next_alloc(iter)) != busy + TRK_LEN
				&& get_val(next))
		{
			if (get_val(iter) > get_val(next))
			{
				swap_mem(iter, next);
				sorted = 0;
			}
			iter = next;
		}
	}
}
