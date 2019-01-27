/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:08:55 by lportay           #+#    #+#             */
/*   Updated: 2018/12/17 18:32:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buf.h"

void	buf_c(t_buf *b, char c)
{
	b->buf[b->written++ % BUFF_SIZE] = c;
	if ((b->written % BUFF_SIZE) == 0)
		write(b->fd, b->buf, BUFF_SIZE);
}

void	buf_nc(t_buf *b, char c, unsigned n)
{
	while (n--)
		buf_c(b, c);
}

void	buf_s(t_buf *b, char *s)
{
	while (*s)
		buf_c(b, *s++);
}

void	buf_ns(t_buf *b, char *s, unsigned n)
{
	while (*s && n--)
		buf_c(b, *s++);
}
