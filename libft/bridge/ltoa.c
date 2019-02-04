/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:53:19 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 15:09:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bridge.h"

char	*ltoa(long n)
{
	char			*s;
	unsigned long	m;
	unsigned		i;

	i = lwidth(n);
	m = (n < 0) ? -n : n;
	if (!(s = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i--] = '\0';
	s[i--] = (m % 10) + '0';
	while ((m /= 10) != 0)
		s[i--] = (m % 10) + '0';
	if (n < 0)
		s[0] = '-';
	return (s);
}

/*
** Maybe implement a faster functioon with reference table t[16]
** [0] = '0', [1] = '1', ... , [10] = 'A', 11 = 'B', ... , [15] = 'F'
*/

char	*ltox(unsigned long n)
{
	char			*s;
	unsigned long	m;
	unsigned		i;

	m = n;
	i = base_width(n, 16) + 2;
	if (!(s = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i--] = '\0';
	if ((m % 16) > 9)
		s[i--] = (m % 16) + 55;
	else
		s[i--] = (m % 16) + '0';
	while ((m /= 16) != 0)
	{
		if ((m % 16) > 9)
			s[i--] = (m % 16) + 55;
		else
			s[i--] = (m % 16) + '0';
	}
	s[0] = '0';
	s[1] = 'x';
	return (s);
}

/*
** char	*ltoa_base(unsigned long n, unsigned char base)
*/
