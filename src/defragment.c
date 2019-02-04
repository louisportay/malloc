/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:25:42 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 12:38:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	defragment_next_blk(t_mem *prev, t_mem *p, t_mem *next)
{
	t_mem *n;

	if (prev)
		set_next(prev, p);
	add_len(p, get_len(next));
	set_prev(p, prev);
	n = get_next(next);
	set_next(p, n);
	if (n)
		set_prev(n, p);
	return (1);
}

/*
** The free block after the one being deallocated has been found
** The previous one might be NULL
**
** If a defragmentation has been performed, the function returns 1, 0 otherwise.
**
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

int		soft_defragment(t_mem *prev, t_mem *p, t_mem *next)
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
		return (defragment_next_blk(prev, p, next));
	return (0);
}
