/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:55:15 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 16:15:49 by lportay          ###   ########.fr       */
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

int				check_alloc(void *p)
{
	t_mem *iter;

	iter = g_m.tracked;
	while (iter != (g_m.tracked + TRK_LEN) && get_val(iter) != p
			&& get_val(iter) != NULL)
		iter = next_alloc(iter);
	if (iter == g_m.tracked + TRK_LEN || !get_val(iter))
		return (-1);
	else if (get_val(iter) == p)
		return (0);
	return (-1);
}

/*
** |== Len ==| |== Value ==|
*/

void			push_alloc(t_mem *busy, t_mem *m)
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

void			pop_alloc(t_mem *busy, t_mem *m)
{
	t_mem *iter;
	t_mem *l;

	iter = busy;
	while (iter != (busy + TRK_LEN) && get_val(iter) != NULL
			&& get_val(iter) != m)
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
