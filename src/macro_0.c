/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:02:44 by lportay           #+#    #+#             */
/*   Updated: 2019/02/01 16:35:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This set of functions shuold be implemented with macros
** Sorry about that
** I wish i could do so
** But the school standard prevents me from doing it
*/

void	set_prev(t_mem *m, void *v)
{
	*(void **)(m + HEADER_SIZE) = v;
}

t_mem	*get_prev(t_mem *m)
{
	return (*(void **)(m + HEADER_SIZE));
}

void	set_next(t_mem *m, void *v)
{
	*(void **)(m + HEADER_SIZE + sizeof(void *)) = v;
}

t_mem	*get_next(t_mem *m)
{
	return (*(void **)(m + HEADER_SIZE + (sizeof(void *))));
}
