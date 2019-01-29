/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:52:59 by lportay           #+#    #+#             */
/*   Updated: 2019/01/29 12:22:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define NO_ENV 1

static void	err(char err)
{
	if (err == NO_ENV)
		write(STDERR_FILENO, "MallocTrackMemory environment variable not set\n",
				47);
}

/*
** Take a string (s) and an adress (ptr) as parameters and store
** the hexadecimal representation in it
**
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

static void	*iter_tracked_mem(t_mem *m, size_t limit, t_buf *b, size_t *bytes)
{
	char	s[32];

	while (m != g_m.tracked + TRK_LEN && get_val(m) && get_len(m) <= limit)
	{
		buf_s(b, addr(s, get_val(m)));
		buf_s(b, " - ");
		buf_s(b, addr(s, get_val(m) + get_len(m)));
		buf_s(b, " : ");
		*bytes += get_len(m);
		buf_s(b, len(s, get_len(m)));
		buf_s(b, " octets\n");
		m = next_alloc(m);
	}
	return (m);
}

/*
** Overkill function, try to avoid its use
*/

void			show_alloc_mem()
{
	t_buf	b;
	t_mem	*m;
	size_t	bytes;
	char	s[32];

	if (!getenv("MallocTrackMemory") || g_m.tracked == NULL)
		return (err(NO_ENV));

	bytes = 0;

	sort_alloc(g_m.tracked);

	buf_init(&b, STDOUT_FILENO);

	buf_s(&b, "TINY : ");
	buf_s(&b, addr(s, g_m.pre_alloc));
	buf_c(&b, '\n');
	m = iter_tracked_mem(g_m.tracked, TINY, &b, &bytes);

	buf_s(&b, "SMALL : ");
	buf_s(&b, addr(s, g_m.pre_alloc + TINY_LEN));
	buf_c(&b, '\n');
	m = iter_tracked_mem(m, SMALL, &b, &bytes);

	buf_s(&b, "LARGE : ");
	buf_s(&b, addr(s, g_m.pre_alloc + PRE_ALLOC_LEN));
	buf_c(&b, '\n');
	iter_tracked_mem(m, (size_t)-1, &b, &bytes);

	buf_s(&b, "Total : ");
	buf_s(&b, len(s, bytes));
	buf_s(&b, " octets\n");

	buf_reset(&b);
}
