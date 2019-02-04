/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:10:53 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 17:20:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Refine the first block found with a best fit algorithm
** 'm' is the first fittable block found, 'len' its size and 's' the exact size
*/

static t_mem	*best_fit_large(t_mem *m, size_t len, size_t s)
{
	t_mem	*v;
	size_t	l;

	v = m;
	m = get_next(m);
	while (m && (l = get_len(m)) != s)
	{
		if (l > s && l < len)
		{
			v = m;
			len = l;
		}
		m = get_next(m);
	}
	if (l == s)
		cut(m);
	else
	{
		m = v;
		shorten(m, s);
	}
	return (m);
}

/*
** Make a first fit search to find one spot in the 'large' pool
**
** the condition (len == s) is an exact match on first match,
** it is highly unlikely to happen
**
** Usually it will match a bigger chunk and will try to reduce the size match
** to a perfect fit with 'best_fit_large'
*/

t_mem			*get_mem_large(t_mem **mem, size_t s)
{
	t_mem	*m;
	size_t	len;

	m = *mem;
	len = 0;
	while (m && (len = get_len(m)) < s)
		m = get_next(m);
	if (len == s)
		cut(m);
	else if (m)
		m = best_fit_large(m, len, s);
	else if (!m)
		return (NULL);
	if (m == *mem)
		*mem = get_next(*mem);
	return (m);
}

void			*large_alloc(t_mem **mem, size_t s)
{
	void *r;

	if (*mem && (r = get_mem_large(mem, s)) != NULL)
		return (r);
	else
	{
		r = mmap(g_m.pre_alloc + PRE_ALLOC_LEN, s,
				PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		if (r == MAP_FAILED)
			return (NULL);
		set_len(r, s);
		return (r);
	}
}
