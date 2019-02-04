/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:19:50 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 16:21:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Take a string (s) and an adress (ptr) as parameters and store
** the hexadecimal representation in it
*/

char	*addr(char *s, void *ptr)
{
	unsigned long	m;
	unsigned		i;

	m = (unsigned long)ptr;
	i = base_width(m, 16) + 2;
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

char	*len(char *s, size_t len)
{
	unsigned		i;

	i = uwidth(len);
	s[i--] = '\0';
	s[i--] = (len % 10) + '0';
	while ((len /= 10) != 0)
		s[i--] = (len % 10) + '0';
	return (s);
}
