/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isunicode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:51:52 by lportay           #+#    #+#             */
/*   Updated: 2018/12/13 18:49:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is.h"

int	is_valid_unicode(wchar_t c)
{
	if ((MB_CUR_MAX == 1 && c > 0xFF) || (MB_CUR_MAX == 2 && c > 0xFFFF))
		return (0);
	else
		return (c >= 0x0 && c <= 0x10FFFF && (c < 0xD800 || c > 0xDFFF));
}

int	isunicode(wchar_t c)
{
	return (c >= 0x0 && c <= 0x10FFFF && (c < 0xD800 || c > 0xDFFF));
}
