/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:52:59 by lportay           #+#    #+#             */
/*   Updated: 2019/01/25 20:18:02 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	err()
{
	write(STDOUT_FILENO, "MallocTrackMemory environment variable not set.\n",
			48);
}

/*
** Overkill function, try to avoid his use
*/

void			show_alloc_mem()
{
	if (!getenv("MallocTrackMemory"))
		return (err());

	// sort g_m.tracked
	// display  g_m.tracked
}
