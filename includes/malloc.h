/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:36:25 by lportay           #+#    #+#             */
/*   Updated: 2019/01/22 19:00:26 by lportay          ###   ########.fr       */
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

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>//
#include <assert.h>//

// s -> size
// rs -> real size
#define DUMP_MEM(M) printf("%p\n", M);
#define LEN(L) printf("%lu\n", L);

#define PRE_ALLOC 0xC99000
//	(2 << 9 + 2 << 16) * 100

#define SMALL_LEN 0xC80000
// (2 << 16) * 100
#define TINY_LEN 0x19000
// (2 << 9) * 100
#define MIN_ALLOC 32
// 8 bytes to store len
// 8 bytes to store prev
// 8 bytes to store next
// 8 bytes for alignment

#define SMALL 0x20000
#define TINY 0x400

typedef void t_mem;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif
