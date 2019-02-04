/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:06:16 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 15:10:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bridge.h"

unsigned	uwidth(unsigned long nb)
{
	unsigned		width;

	width = 1;
	while ((nb /= 10) != 0)
		width++;
	return (width);
}

unsigned	lwidth(long nb)
{
	unsigned long	nbr;
	unsigned		width;

	nbr = (nb > 0) ? nb : -nb;
	width = (nb >= 0) ? 1 : 2;
	while ((nbr /= 10) != 0)
		width++;
	return (width);
}

unsigned	base_width(size_t nb, unsigned char base)
{
	unsigned				width;

	width = 1;
	while ((nb /= base) != 0)
		width++;
	return (width);
}
