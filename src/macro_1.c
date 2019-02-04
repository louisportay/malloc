/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:02:44 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 12:17:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	set_len(t_mem *m, size_t len)
{
	*((size_t *)(m)) = len;
}

void	add_len(t_mem *m, size_t len)
{
	*((size_t *)(m)) += len;
}

size_t	get_len(t_mem *m)
{
	return (*((size_t *)(m)));
}

/*
** Test whether m1 and m2 are contiguous
*/

int		adj_mem(t_mem *m1, t_mem *m2)
{
	return (m1 + get_len(m1) == m2);
}
