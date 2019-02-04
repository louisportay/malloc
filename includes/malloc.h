/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:36:25 by lportay           #+#    #+#             */
/*   Updated: 2019/02/04 17:19:29 by lportay          ###   ########.fr       */
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
** On Mac OS X, prefix './run.sh' with your command to load your malloc
** in the program
*/

/*
** The pointer returned by malloc should ideally aligned by 16 bytes, at least
** by 8 bytes
*/

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "bridge.h"
# include "buf.h"
# include "mem.h"
# include "maths.h"

/*
** # define SET_PREV(M, V)	*(void **)(M + HEADER_SIZE) = V
** # define GET_PREV(M)		*(void **)(M + HEADER_SIZE)
** # define SET_NEXT(M, V)	*(void **)(M + HEADER_SIZE+ (sizeof(void *))) = V
** # define GET_NEXT(M)		*(void **)(M + HEADER_SIZE+ (sizeof(void *)))
** # define ADD_LEN(M, L)	*(size_t *)M += L
** # define SET_LEN(M, L)	*(size_t *)M = L
** # define GET_LEN(M)		*((size_t *)M)
*/

/*
** Convenience Macros
**
** # define LEN(L) len(s, L); write(1, s, strlen(s)); write(1, "\n", 1)
** # define PTR(P) addr(s, P); write(1, s, strlen(s)); write(1, "\n", 1)
*/

/*
** HEADER_SIZE represents the size necessary to store the block length
** MIN_ALLOC is the minimum allocation to store the 'prev' and 'next' pointer
*/

# define HEADER_SIZE 16
# define MIN_ALLOC 16

/*
** PRE_ALLOC_LEN asks for SMALL_LEN + TINY_LEN memory (153 pages)
** SMALL_LEN -> 128 pages (100 allocations SMALL)
** TINY_LEN => 25 pages (128 allocations TINY)
*/

# define PRE_ALLOC_LEN 0xCA0 * getpagesize()
# define SMALL_LEN 0xC80 * getpagesize()
# define TINY_LEN 0x20 * getpagesize()

/*
** The two maximum sizes for each zone
** TINY -> 1024
** SMALL -> 1310172
** LARGE is virtually unlimited
*/

# define SMALL 0x20000
# define TINY 0x400

/*
** 4096 allocations tracked, 10 pages asked
*/

# define TRK_LEN 0x10000

/*
** The maximum size for pooling large blocks
** beyond that size the block is immediately freed
*/

# define LARGE_THRESHOLD 0x40000

typedef void			t_mem;

struct					s_mem
{
	t_mem				*tiny;
	t_mem				*small;
	t_mem				*large;
	void				*pre_alloc;
	t_mem				*tracked;
};

extern struct s_mem		g_m;
extern pthread_mutex_t	g_lock;

/*
** Public API
*/

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					*calloc(size_t count, size_t size);
void					show_free_mem();
void					show_alloc_mem();

/*
** Internal API
*/

void					set_prev(t_mem *m, void *v);
t_mem					*get_prev(t_mem *m);
void					set_next(t_mem *m, void *v);
t_mem					*get_next(t_mem *m);
void					set_len(t_mem *m, size_t len);
void					add_len(t_mem *m, size_t len);
size_t					get_len(t_mem *m);

void					shorten(t_mem *m, size_t rs);
void					cut(t_mem *m);

int						adj_mem(t_mem *m1, t_mem *m2);
int						soft_defragment(t_mem *prev, t_mem *p, t_mem *next);

void					*large_alloc(t_mem **mem, size_t s);

/*
** MallocTrackMemory API
*/

/*
** # define GET_VAL(M)		*(void **)(M + (sizeof(void *)));
** # define SET_VAL(M, V)	*(void **)(M + (sizeof(void *))) = V;
*/

void					set_val(t_mem *m, t_mem *v);
t_mem					*get_val(t_mem *m);
t_mem					*next_alloc(t_mem *m);
void					push_alloc(t_mem *busy, t_mem *m);
void					pop_alloc(t_mem *busy, t_mem *m);
void					sort_alloc(t_mem *busy);
int						check_alloc(void *p);
char					*addr(char *s, void *ptr);
char					*len(char *s, size_t len);

#endif
