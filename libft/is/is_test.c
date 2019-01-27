/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:16 by lportay           #+#    #+#             */
/*   Updated: 2019/01/14 21:19:21 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "is.h"
#include "colors.h"

int	flatten(int i)
{
	if (i > 0)
		return (1);
	else if (i < 0)
		return (-1);
	else
		return (i);
}

/*
** int	main(void)
** {
** 	assert(isalnum(' ') == ft_isalnum(' '));
** 	assert(isalnum('\0') == ft_isalnum('\0'));
** 	assert(flatten(isalnum('A')) == flatten(ft_isalnum('A')));
** 	assert(flatten(isalnum('a')) == flatten(ft_isalnum('a')));
** 	assert(flatten(isalnum('0')) == flatten(ft_isalnum('0')));
** 	assert(isalnum(';') == ft_isalnum(';'));
**
** 	assert(flatten(isalpha(' ')) == flatten(ft_isalpha(' ')));
** 	assert(flatten(isalpha('A')) == flatten(ft_isalpha('A')));
** 	assert(flatten(isalpha('0')) == flatten(ft_isalpha('0')));
** 	assert(flatten(isalpha(0)) == flatten(ft_isalpha(0)));
**
** 	assert(flatten(isascii(' ')) == flatten(ft_isascii(' ')));
** 	assert(flatten(isascii(255)) == flatten(ft_isascii(155)));
** 	assert(flatten(isascii(127)) == flatten(ft_isascii(127)));
** 	assert(flatten(isascii(-1)) == flatten(ft_isascii(-1)));
**
** 	assert(flatten(isblank(' ')) == flatten(ft_isblank(' ')));
** 	assert(flatten(isblank('	')) == flatten(ft_isblank('	')));
** 	assert(flatten(isblank('\v')) == ft_isblank('\v'));
** 	assert(flatten(isblank('\n')) == ft_isblank('\n'));
**
** 	assert(flatten(iscntrl(' ')) == flatten(ft_iscntrl(' ')));
** 	assert(flatten(iscntrl(127)) == flatten(ft_iscntrl(127)));
** 	assert(flatten(iscntrl(0)) == flatten(ft_iscntrl(0)));
** 	assert(flatten(iscntrl('8')) == flatten(ft_iscntrl('8')));
**
** 	assert(flatten(isdigit(' ')) == flatten(ft_isdigit(' ')));
** 	assert(flatten(isdigit('0')) == flatten(ft_isdigit('0')));
** 	assert(flatten(isdigit('9')) == flatten(ft_isdigit('9')));
** 	assert(flatten(isdigit('0' - 1)) == flatten(ft_isdigit('0' -1)));
**
**
** 	assert(flatten(isgraph(' ')) == flatten(ft_isgraph(' ')));
** 	assert(flatten(isgraph('\f')) == flatten(ft_isgraph('\f')));
** 	assert(flatten(isgraph('U')) == flatten(ft_isgraph('U')));
** 	assert(flatten(isgraph(127)) == flatten(ft_isgraph(127)));
** 	assert(flatten(isgraph('	')) == flatten(ft_isgraph('	')));
**
** 	assert(flatten(islower(' ')) == flatten(ft_islower(' ')));
** 	assert(flatten(islower('A')) == flatten(ft_islower('A')));
** 	assert(flatten(islower('a')) == flatten(ft_islower('a')));
** 	assert(flatten(islower(128)) == flatten(ft_islower(128)));
**
** 	assert(flatten(isprint(' ')) == flatten(ft_isprint(' ')));
** 	assert(flatten(isprint('	')) == flatten(ft_isprint('	')));
** 	assert(flatten(isprint('!')) == flatten(ft_isprint('!')));
** 	assert(flatten(isprint(0)) == flatten(ft_isprint(0)));
**
** 	assert(flatten(ispunct(' ')) == flatten(ft_ispunct(' ')));
** 	assert(flatten(ispunct(',')) == flatten(ft_ispunct(',')));
** 	assert(flatten(ispunct('!')) == flatten(ft_ispunct('!')));
** 	assert(flatten(ispunct('a')) == flatten(ft_ispunct('a')));
** 	assert(flatten(ispunct('8')) == flatten(ft_ispunct('8')));
**
** 	assert(flatten(isspace(' ')) == flatten(ft_isspace(' ')));
** 	assert(flatten(isspace(0)) == flatten(ft_isspace(0)));
** 	assert(flatten(isspace('\v')) == flatten(ft_isspace('\v')));
** 	assert(flatten(isspace('	')) == flatten(ft_isspace('	')));
** 	assert(flatten(isspace('k')) == flatten(ft_isspace('k')));
**
** 	assert(flatten(isupper(' ')) == flatten(ft_isupper(' ')));
** 	assert(flatten(isupper('9')) == flatten(ft_isupper('9')));
** 	assert(flatten(isupper('J')) == flatten(ft_isupper('J')));
** 	assert(flatten(isupper('K')) == flatten(ft_isupper('K')));
** 	assert(flatten(isupper('k')) == flatten(ft_isupper('k')));
**
** 	assert(flatten(isxdigit(' ')) == flatten(ft_isxdigit(' ')));
** 	assert(flatten(isxdigit('e')) == flatten(ft_isxdigit('e')));
** 	assert(flatten(isxdigit('x')) == flatten(ft_isxdigit('x')));
** 	assert(flatten(isxdigit('F')) == flatten(ft_isxdigit('F')));
** 	assert(flatten(isxdigit('1')) == flatten(ft_isxdigit('1')));
** 	assert(flatten(isxdigit(127)) == flatten(ft_isxdigit(127)));
**
** 	puts(GREEN"OK"RESET);
** }
*/
