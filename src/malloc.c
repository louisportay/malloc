/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:00:57 by lportay           #+#    #+#             */
/*   Updated: 2019/01/23 18:28:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	set_prev(t_mem *m, void *v)
{
	*(void **)(m + sizeof(void *)) = v;
}

t_mem	*get_prev(t_mem *m)
{
	return *(void **)(m + sizeof(void *));
}

void	set_next(t_mem *m, void *v)
{
	*(void **)(m + (sizeof(void *) << 1)) = v;
}

t_mem	*get_next(t_mem *m)
{	
	return *(void **)(m + (sizeof(void *) << 1));
}

void	set_len(t_mem *m, size_t len)
{
	*(size_t *)m = len;
}

size_t	get_len(t_mem *m)
{
	return *((size_t *)m);
}

void	init_mem(t_mem *m)
{
	t_mem *c;

	set_len(m, TINY_LEN);
	set_prev(m, NULL);
	set_next(m, m + TINY_LEN);

	c = get_next(m);

	set_len(c, SMALL_LEN);
	set_prev(c, m);
	set_next(c, NULL);

	assert(c - m == TINY_LEN);
	assert(get_len(c) == SMALL_LEN);
}

int		alloc_mem(t_mem **m)
{
	*m = mmap(NULL, PRE_ALLOC, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (*m == MAP_FAILED)
		return (-1);
	return (0);
}

void	shorten(t_mem *m, size_t rs)
{
	size_t	len;
	void	*prev;
	void	*next;
	void	*p;

	len = get_len(m);
	prev = get_prev(m);
	next = get_next(m);

	set_next(m, m + rs);

	m += rs;
	set_len(m, len - rs);
	set_prev(m, prev);
	set_next(m, next);

	if ((p = get_prev(m)) != NULL)
		set_next(p, m);
	if ((p = get_next(m)) != NULL)
		set_prev(p, m);
}

void	cut(t_mem *m)
{
	t_mem *p;

	if ((p = get_prev(m)) != NULL)
		set_next(p, get_next(m));
	if ((p = get_next(m)) != NULL)
		set_prev(p, get_prev(m));
}

void	*get_mem(t_mem **mem, size_t s)
{
	t_mem	*m;

	m = *mem;
	if (s < MIN_ALLOC)
		s = MIN_ALLOC;
	else
		s += sizeof(size_t);

	while (get_len(m) < s && m)
		m = get_next(m);
	if (!m)
		// defragmenter et relancer la recherche
		return (NULL);
	if (get_len(m) == s)
		cut(m);
	else
		shorten(m, s);

	if (m == *mem)
	{
		*mem = get_next(*mem);
		assert(*mem - m == (long)s);
	}
	return (m);
}

void	*large_alloc(t_mem **mem, size_t s)
{
	if (*mem)
	{
		t_mem *m;

		m = *mem;
		// implementer best-fit 

		//while (get_len(m) < s && m)
		//	m = get_next(m);

		if (m)
		{
			// cut and return
		}

	}
	else
		// mmap +8 des familles, set la len et return
}

void	*_malloc(size_t size)
{
	static t_mem	*t_free;
	static t_mem	*s_free;
	static t_mem	*l_free;
	void			*r;

	if (t_free == NULL)
	{
		if (alloc_mem(&t_free) == -1)
			return (NULL);
		init_mem(t_free);
		s_free = get_next(t_free);
	}
	if (size <= TINY)
		r = get_mem(&t_free, size);
	else if (size <= SMALL)
		r = get_mem(&s_free, size);
	else
		r = large_alloc(&l_free, size);
	return (r + sizeof(size_t));//
}

#include <string.h> //

int main(void)
{
	void *s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	 s = _malloc(16);
	DUMP_MEM(s);
	void *q = _malloc(16);
	DUMP_MEM(q);
	strcpy(q, "0123456789");
	printf("%s\n", q);
}
