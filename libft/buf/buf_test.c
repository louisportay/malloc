/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:12 by lportay           #+#    #+#             */
/*   Updated: 2019/01/14 21:19:43 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include "buf.h"

int	main(void)
{
	t_buf b;

	buf_init(&b, STDOUT_FILENO);
	setlocale(LC_ALL, "");
	buf_nwc(&b, 129412, 3);
	buf_l(&b, -2326327645327L);
	buf_c(&b, '\n');
	buf_reset(&b);
}
