/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:04:50 by lportay           #+#    #+#             */
/*   Updated: 2019/01/24 15:10:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This shorten the memory block
** and restore the links
** It has the downside of fragmenting memory
*/

void	shorten(t_mem *m, size_t rs)
{
	size_t	len;
	void	*prev;
	void	*next;
	void	*p;

	len = get_len(m);
	prev = get_prev(m);
	next = get_next(m);
	set_next(m, m + rs);
	m += rs;
	set_len(m, len - rs);
	set_prev(m, prev);
	set_next(m, next);
	if ((p = get_prev(m)) != NULL)
		set_next(p, m);
	if ((p = get_next(m)) != NULL)
		set_prev(p, m);
}

void	cut(t_mem *m)
{
	t_mem *p;

	if ((p = get_prev(m)) != NULL)
		set_next(p, get_next(m));
	if ((p = get_next(m)) != NULL)
		set_prev(p, get_prev(m));
}
