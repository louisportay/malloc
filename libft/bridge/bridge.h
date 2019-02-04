/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:48:42 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 15:10:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRIDGE_H
# define BRIDGE_H

# include <stdlib.h>
# include "is.h"

long		ft_atol(const char *nptr);
char		*ltoa(long n);
char		*ltox(unsigned long n);
unsigned	uwidth(unsigned long nb);
unsigned	lwidth(long nb);
long		ft_abs(long n);
void		lswap(long *a, long *b);
void		iswap(int *a, int *b);
unsigned	base_width(size_t nb, unsigned char base);

/*
** void		swap(void *a, void *b, size_t size);
**
** # include "list.h"
**
** --> list_from_array
*/

#endif
