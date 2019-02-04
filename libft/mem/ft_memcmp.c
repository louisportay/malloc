/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:55:28 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 15:04:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *p1;
	const unsigned char *p2;

	if (!n)
		return (0);
	p1 = s1;
	p2 = s2;
	while (*p1 == *p2 && n-- != 1)
	{
		p1++;
		p2++;
	}
	if (!n)
		return (0);
	return (*p1 - *p2);
}
