/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:02:44 by lportay           #+#    #+#             */
/*   Updated: 2019/01/24 15:04:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This set of functions shuold be implemented with C macros
** Sorry about that
** I wish i could do it
*/

void	set_prev(t_mem *m, void *v)
{
	*(void **)(m + sizeof(void *)) = v;
}

t_mem	*get_prev(t_mem *m)
{
	return *(void **)(m + sizeof(void *));
}

void	set_next(t_mem *m, void *v)
{
	*(void **)(m + (sizeof(void *) << 1)) = v;
}

t_mem	*get_next(t_mem *m)
{	
	return *(void **)(m + (sizeof(void *) << 1));
}

void	set_len(t_mem *m, size_t len)
{
	*(size_t *)m = len;
}

size_t	get_len(t_mem *m)
{
	return *((size_t *)m);
}
