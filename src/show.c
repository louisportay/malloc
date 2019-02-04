/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:52:59 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 17:21:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

void		show_free_mem(void)
{
	t_buf	b;

	pthread_mutex_lock(&g_lock);
	buf_init(&b, STDOUT_FILENO);
	iter_free_mem(&b, g_m.tiny);
	iter_free_mem(&b, g_m.small);
	iter_free_mem(&b, g_m.large);
	buf_reset(&b);
	pthread_mutex_unlock(&g_lock);
}

static void	fill_buffer(t_buf *b)
{
	char	s[32];
	size_t	total[2];
	t_mem	*m;

	total[0] = 0;
	total[1] = 0;
	buf_s(b, "TINY : ");
	buf_s(b, addr(s, g_m.pre_alloc));
	buf_c(b, '\n');
	m = iter_tracked_mem(g_m.tracked, TINY, b, total);
	buf_s(b, "SMALL : ");
	buf_s(b, addr(s, g_m.pre_alloc + TINY_LEN));
	buf_c(b, '\n');
	m = iter_tracked_mem(m, SMALL, b, total);
	buf_s(b, "LARGE : ");
	buf_s(b, addr(s, g_m.pre_alloc + PRE_ALLOC_LEN));
	buf_c(b, '\n');
	iter_tracked_mem(m, (size_t)-1, b, total);
	buf_s(b, "Total : ");
	buf_s(b, len(s, total[0]));
	buf_s(b, " octets pour ");
	buf_s(b, len(s, total[1]));
	buf_s(b, " allocations\n");
}

/*
** Overkill function, try to avoid its use
** total[0] is bytes count
** total[1] is alloc count
*/

void		show_alloc_mem(void)
{
	t_buf	b;

	if (g_m.pre_alloc == NULL)
		return ;
	pthread_mutex_lock(&g_lock);
	sort_alloc(g_m.tracked);
	buf_init(&b, STDOUT_FILENO);
	fill_buffer(&b);
	buf_reset(&b);
	pthread_mutex_unlock(&g_lock);
}
