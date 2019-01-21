/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:36:25 by lportay           #+#    #+#             */
/*   Updated: 2019/01/21 18:51:19 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** Authorized Functions
** write (2)
** mmap (2)
** munmap (2)
** getpagesize (3)
** getrlimit (2)
*/

/*
** On Mac OS X, source the file '_setup.sh' to load your malloc on the session
*/

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif
