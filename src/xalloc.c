/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:36:23 by lportay           #+#    #+#             */
/*   Updated: 2019/01/28 19:54:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void *r;

	if (!ptr)
		return (malloc(size));
	else if (g_m.pre_alloc == NULL)
		return (NULL);

	if (size < MIN_ALLOC)
		size = MIN_ALLOC;

	if (get_len(ptr - sizeof(size_t)) - sizeof(size_t) >= size)
		return (ptr);

	if (!(r = malloc(size)))
		return (NULL);
	ft_memmove(r, ptr, size);
	free(ptr);
	return (r);
}

void	*calloc(size_t count, size_t size)
{
	void	*r;
	size_t	total;

	total = count * size;
	if (!(r = malloc(total)))
		return (NULL);
	ft_memset(r, 0, total);
	return (r);
}
