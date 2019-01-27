/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:18:05 by lportay           #+#    #+#             */
/*   Updated: 2018/12/17 18:34:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buf.h"

void	buf_init(t_buf *b, int fd)
{
	b->fd = fd;
	b->written = 0;
}

size_t	buf_reset(t_buf *b)
{
	int r;

	write(b->fd, b->buf, b->written % BUFF_SIZE);
	r = b->written;
	b->written = 0;
	return (r);
}
