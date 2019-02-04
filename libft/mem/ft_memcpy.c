/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:19 by lportay           #+#    #+#             */
/*   Updated: 2019/01/14 21:20:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char	*iter;

	iter = dst;
	while (n-- > 0)
		*iter++ = *(unsigned char *)src++;
	return (dst);
}
