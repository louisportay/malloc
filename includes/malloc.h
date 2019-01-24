/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:36:25 by lportay           #+#    #+#             */
/*   Updated: 2019/01/24 15:40:42 by lportay          ###   ########.fr       */
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

//
#define SET_PREV(M, V)	*(void **)(M + sizeof(void *)) = V
#define GET_PREV(M)		*(void **)(M + sizeof(void *))
#define SET_NEXT(M, V)	*(void **)(M + (sizeof(void *) << 1)) = V
#define GET_NEXT(M)		*(void **)(M + (sizeof(void *) << 1))
#define SET_LEN(M, L)	*(size_t *)M = L
#define GET_LEN(M)		*((size_t *)M)
//

// s -> size
// rs -> real size
#define DEBUG printf("DEBUG\n")
#define DUMP_MEM(M) printf("%p\n", M)
#define LEN(L) printf("%lu\n", L)

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


void	set_prev(t_mem *m, void *v);
t_mem	*get_prev(t_mem *m);
void	set_next(t_mem *m, void *v);
t_mem	*get_next(t_mem *m);
void	set_len(t_mem *m, size_t len);
size_t	get_len(t_mem *m);

void	shorten(t_mem *m, size_t rs);
void	cut(t_mem *m);

void	*large_alloc(t_mem **mem, size_t s);

#endif
