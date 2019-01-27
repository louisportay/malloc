/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:14:40 by lportay           #+#    #+#             */
/*   Updated: 2018/12/14 19:50:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bridge.h"

long		ft_atol(const char *str)
{
	int		sign;
	long	nb;

	sign = 1;
	nb = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + *str++ - '0';
	return (sign * nb);
}
