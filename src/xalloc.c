/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:36:23 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 12:53:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** SCHEME FOR PTR HEADERS IN REALLOC
**
** 'ptr' in params
**
** L  P
** ===|============
**
**
**
*/

void	*realloc(void *ptr, size_t size)
{
	void *r;

	if (!ptr)
		return (malloc(size));
	//pthread_mutex_lock(&g_lock);
	if (check_alloc(ptr - HEADER_SIZE) == -1)
	{
		//pthread_mutex_unlock(&g_lock);
		return (NULL);
	}

	if (size < MIN_ALLOC)
		size = MIN_ALLOC;
	size = uround(size, 16);

	if (get_len(ptr - HEADER_SIZE) - HEADER_SIZE >= size)
	{
		//pthread_mutex_unlock(&g_lock);
		return (ptr);
	}
	//pthread_mutex_unlock(&g_lock);
	if (!(r = malloc(size)))
		return (NULL);

	//pthread_mutex_lock(&g_lock);

	ft_memmove(r, ptr, get_len(ptr - HEADER_SIZE) - HEADER_SIZE);
	//pthread_mutex_unlock(&g_lock);
	free(ptr);
	return (r);
}

void	*calloc(size_t count, size_t size)
{
	void	*r;
	size_t	total;

	//pthread_mutex_lock(&g_lock);
	total = count * size;
	//pthread_mutex_unlock(&g_lock);
	if (!(r = malloc(total)))
		return (NULL);
	//pthread_mutex_lock(&g_lock);
	ft_bzero(r, total);
	//pthread_mutex_unlock(&g_lock);
	return (r);
}
