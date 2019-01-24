/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:10:53 by lportay           #+#    #+#             */
/*   Updated: 2019/01/24 15:42:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"

/*
** Refine the first spot found with a best fit algorithm
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
*/

t_mem			*get_mem_large(t_mem **mem, size_t s)
{
	t_mem	*m;
	size_t	len;

	m = *mem;
	len = 0;
	while (m && (len = get_len(m)) < s)
		m = get_next(m);
	if (len == s) // exact match -- highly unlikely to happen
		cut(m);
	else if (m) // found some bigger chunk
		m = best_fit_large(m, len, s);
	else if (!m)
		return (NULL);
	if (m == *mem)
		*mem = get_next(*mem);
	return (m);
}

void	*large_alloc(t_mem **mem, size_t s)
{
	void *r;

	s += sizeof(size_t);
	if (*mem && (r = get_mem_large(mem, s)) != NULL)
		return (r);
	else
	{
	   r = mmap(NULL, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	   set_len(r, s);
	   return (r);
	}
}

