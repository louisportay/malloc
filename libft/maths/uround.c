/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uround.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 12:49:59 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 15:07:21 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/*
** 'round' should be a power of two
*/

unsigned	uround(unsigned value, unsigned round)
{
	return ((value + (round - 1)) & ~(round - 1));
}
