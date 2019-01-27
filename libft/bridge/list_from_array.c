/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_from_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:53 by lportay           #+#    #+#             */
/*   Updated: 2019/01/14 21:19:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bridge.h"

/*
** TO BE RE-CHECKED CAREFULLY
**
** The list 'may' be sorted depending on the data stored in the array
** and in which order it is returned by the extractor
*/

t_lst	*list_from_array(void **a, size_t len, t_result (*extract)(void *),
						void (*del)(void *))
{
	t_result	r;
	t_lst		*l;

	l = NULL;
	while (len > 0)
	{
		r = extract(a[--len]);
		while (r.status == OK)
		{
			if (lst_addfront_data(&l, r.data) == -1)
			{
				lst_destroy(&l, &del);
				return (NULL);
			}
			r = extract(a[len]);
		}
		if (r.status == NOMEM || r.status == ERR)
		{
			lst_destroy(&l, &del);
			return (NULL);
		}
	}
	return (l);
}
