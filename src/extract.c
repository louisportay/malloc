/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:04:50 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 16:01:01 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This shorten the memory block
** and restore the links
** It has the downside of fragmenting memory
*/

void	shorten(t_mem *m, size_t s)
{
	size_t	len;
	void	*prev;
	void	*next;

	len = get_len(m);
	prev = get_prev(m);
	next = get_next(m);
	set_len(m, s);
	set_next(m, m + s);
	m += s;
	set_len(m, len - s);
	set_prev(m, prev);
	set_next(m, next);
	if (prev)
		set_next(prev, m);
	if (next)
		set_prev(next, m);
}

/*
** This is a perfect fit into freelist, Well done
*/

void	cut(t_mem *m)
{
	t_mem *p;

	if ((p = get_prev(m)) != NULL)
		set_next(p, get_next(m));
	if ((p = get_next(m)) != NULL)
		set_prev(p, get_prev(m));
}
