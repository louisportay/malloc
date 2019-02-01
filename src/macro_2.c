/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:55:17 by lportay           #+#    #+#             */
/*   Updated: 2019/01/31 14:57:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	*next_alloc(t_mem *m)
{
	return (m + (sizeof(size_t) << 1));
}

void	set_val(t_mem *m, t_mem *v)
{
	*(void **)(m + (sizeof(void *))) = v;
}

t_mem	*get_val(t_mem *m)
{
	return (*(void **)(m + (sizeof(void *))));
}
