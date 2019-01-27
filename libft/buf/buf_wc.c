/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_wc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:52:33 by lportay           #+#    #+#             */
/*   Updated: 2018/12/17 18:15:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buf.h"

int		buf_wc(t_buf *b, wchar_t wc)
{
	if (isunicode(wc) == -1)
		return (-1);
	if (wc <= 0x7F)
		buf_c(b, wc);
	else if (wc <= 0x7FF)
	{
		buf_c(b, ((wc >> 6) & 0b11111) | 0b11000000);
		buf_c(b, (wc & 0b111111) | 0b10000000);
	}
	else if (wc <= 0xFFFF)
	{
		buf_c(b, ((wc >> 12) & 0b1111) | 0b11100000);
		buf_c(b, ((wc >> 6) & 0b111111) | 0b10000000);
		buf_c(b, (wc & 0b111111) | 0b10000000);
	}
	else if (wc <= 0x1FFFFF)
	{
		buf_c(b, ((wc >> 18) & 0b111) | 0b11110000);
		buf_c(b, ((wc >> 12) & 0b111111) | 0b10000000);
		buf_c(b, ((wc >> 6) & 0b111111) | 0b10000000);
		buf_c(b, (wc & 0b111111) | 0b10000000);
	}
	return (0);
}

void	buf_nwc(t_buf *b, wchar_t wc, unsigned n)
{
	while (n--)
		buf_wc(b, wc);
}

void	buf_ws(t_buf *b, wchar_t *ws)
{
	while (*ws)
		buf_wc(b, *ws++);
}

void	buf_nws(t_buf *b, wchar_t *ws, unsigned n)
{
	while (*ws && n--)
		buf_wc(b, *ws++);
}
