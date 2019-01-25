/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:36:25 by lportay           #+#    #+#             */
/*   Updated: 2019/01/25 20:15:32 by lportay          ###   ########.fr       */
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

//Try to exhaust memory by methodically asking for the limit a 100 times
//For Tiny and Small
//peut-etre sauver les pointeurs originaux quelque part et si ils ont une
//valeur mais que ceux d'usage sont sets a NULL, alors renvoyer NULL

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>//
#include <assert.h>//

//
#define SET_PREV(M, V)	*(void **)(M + sizeof(void *)) = V
#define GET_PREV(M)		*(void **)(M + sizeof(void *))
#define SET_NEXT(M, V)	*(void **)(M + (sizeof(void *) << 1)) = V
#define GET_NEXT(M)		*(void **)(M + (sizeof(void *) << 1))
#define ADD_LEN(M, L)	*(size_t *)M += L
#define SET_LEN(M, L)	*(size_t *)M = L
#define GET_LEN(M)		*((size_t *)M)
//

// s -> size
// rs -> real size
#define DEBUG printf("DEBUG\n")
#define DUMP_MEM(M) printf("%p\n", M)
#define DM(M) printf("%p\n", M)
#define DUMP_MEM_BR(S, M) printf("%s %p\n", S, M)
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

#define TRACKLIST 0x2000
//8192
// 8192 / 32 = 256 allocations

#define LARGE_THRESHOLD 0x40000
//262144
#define SMALL 0x20000
//131072
#define TINY 0x400
//1024

typedef void t_mem;

struct s_mem
{
	t_mem	*tiny;
	t_mem	*small;
	t_mem	*large;
	void	*pre_alloc;
	t_mem	*tracked;
};

extern struct s_mem g_m;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
//void	*calloc(size_t count, size_t size);

void	set_prev(t_mem *m, void *v);
t_mem	*get_prev(t_mem *m);
void	set_next(t_mem *m, void *v);
t_mem	*get_next(t_mem *m);
void	set_len(t_mem *m, size_t len);
void	add_len(t_mem *m, size_t len);
size_t	get_len(t_mem *m);
int		adj_mem(t_mem *m1, t_mem *m2);

void	shorten(t_mem *m, size_t rs);
void	cut(t_mem *m);

void	*large_alloc(t_mem **mem, size_t s);

/*
** MallocTrackMemory API
*/

#define GET_VAL(M)		*(void **)(M + (sizeof(void *) * 3));
#define SET_VAL(M, V)	*(void **)(M + (sizeof(void *) * 3)) = V;

void	show_alloc_mem();
void	set_val(t_mem *m, t_mem *v);
t_mem	*get_val(t_mem *m);
void	push_alloc(t_mem **busy, t_mem *m);
void	pop_alloc(t_mem **busy, t_mem *m);
void	sort_alloc(t_mem **busy);

#endif
