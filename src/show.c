/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:52:59 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 12:32:43 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Take a string (s) and an adress (ptr) as parameters and store
** the hexadecimal representation in it
**
*/

/* static */char	*addr(char *s, void *ptr)
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

/*static */char	*len(char *s, size_t len)
{
	unsigned		i;

	i = uwidth(len);
	s[i--] = '\0';
	s[i--] = (len % 10) + '0';
	while ((len /= 10) != 0)
		s[i--] = (len % 10) + '0';
	return (s);
}

static void	*iter_tracked_mem(t_mem *m, size_t limit, t_buf *b, size_t total[2])
{
	char	s[32];

	while (m != g_m.tracked + TRK_LEN && get_val(m) && get_len(m) <= limit)
	{
		buf_s(b, addr(s, get_val(m)));
		buf_s(b, " - ");
		buf_s(b, addr(s, get_val(m) + get_len(m)));
		buf_s(b, " : ");
		total[1]++;
		total[0] += get_len(m);
		buf_s(b, len(s, get_len(m)));
		buf_s(b, " octets\n");
		m = next_alloc(m);
	}
	return (m);
}

static void	iter_free_mem(t_buf *b, void *iter)
{
	char	s[32];

	while (iter)
	{
		buf_s(b, addr(s, iter));
		buf_s(b, " - ");
		buf_s(b, addr(s, iter + get_len(iter)));
		buf_s(b, " : ");
		buf_s(b, len(s, get_len(iter)));
		buf_s(b, " bytes\n");
		iter = get_next(iter);
	}

}

void	show_free_mem()
{
	t_buf	b;

	//pthread_mutex_lock(&g_lock);
	buf_init(&b, STDOUT_FILENO);
	iter_free_mem(&b, g_m.tiny);
	iter_free_mem(&b, g_m.small);
	iter_free_mem(&b, g_m.large);
	buf_reset(&b);
	//pthread_mutex_unlock(&g_lock);
}

/*
** Overkill function, try to avoid its use
** total[0] is bytes count
** total[1] is alloc count
*/

void			show_alloc_mem()
{
	char	s[32];
	size_t	total[2];
	t_buf	b;
	t_mem	*m;

	if (g_m.pre_alloc == NULL)
		return ;
	//pthread_mutex_lock(&g_lock);
	total[0] = 0;
	total[1] = 0;

	sort_alloc(g_m.tracked);

	buf_init(&b, STDOUT_FILENO);

	buf_s(&b, "TINY : ");
	buf_s(&b, addr(s, g_m.pre_alloc));
	buf_c(&b, '\n');
	m = iter_tracked_mem(g_m.tracked, TINY, &b, total);

	buf_s(&b, "SMALL : ");
	buf_s(&b, addr(s, g_m.pre_alloc + TINY_LEN));
	buf_c(&b, '\n');
	m = iter_tracked_mem(m, SMALL, &b, total);

	buf_s(&b, "LARGE : ");
	buf_s(&b, addr(s, g_m.pre_alloc + PRE_ALLOC_LEN));
	buf_c(&b, '\n');
	iter_tracked_mem(m, (size_t)-1, &b, total);

	buf_s(&b, "Total : ");
	buf_s(&b, len(s, total[0]));
	buf_s(&b, " octets pour ");
	buf_s(&b, len(s, total[1]));
	buf_s(&b, " allocations\n");

	buf_reset(&b);
	//pthread_mutex_unlock(&g_lock);
}
