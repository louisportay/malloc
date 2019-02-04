/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:14:07 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 16:16:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This is no algorithm project, so the bubbles will do the job
*/

static void	swap_mem(void *iter, void *next)
{
	void	*i;
	size_t	l;

	i = get_val(iter);
	l = get_len(iter);
	set_val(iter, get_val(next));
	set_len(iter, get_len(next));
	set_val(next, i);
	set_len(next, l);
}

void		sort_alloc(t_mem *busy)
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
