/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:36:23 by lportay           #+#    #+#             */
/*   Updated: 2019/01/30 10:43:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*unlock(void *ptr)
{
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void *r;

	if (!ptr)
		return (malloc(size));
	else if (g_m.pre_alloc == NULL)
		return (NULL);

	pthread_mutex_lock(&g_lock);
	if (size < MIN_ALLOC)
		size = MIN_ALLOC;

	if (get_len(ptr - sizeof(size_t)) - sizeof(size_t) >= size)
		return (unlock(ptr));

	if (!(r = malloc(size)))
		return (unlock(NULL));
	ft_memmove(r, ptr, size);
	free(ptr);
	pthread_mutex_unlock(&g_lock);
	return (r);
}

void	*calloc(size_t count, size_t size)
{
	void	*r;
	size_t	total;

	pthread_mutex_lock(&g_lock);
	total = count * size;
	if (!(r = malloc(total)))
		return (unlock(NULL));
	ft_memset(r, 0, total);
	pthread_mutex_unlock(&g_lock);
	return (r);
}
