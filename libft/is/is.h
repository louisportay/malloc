/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:48:42 by lportay           #+#    #+#             */
/*   Updated: 2018/12/13 18:49:02 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_H
# define IS_H

# include <stdlib.h>
# include <wchar.h>

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_iscntrl(int c);
int ft_isdigit(int c);
int ft_isgraph(int c);
int ft_islower(int c);
int ft_isprint(int c);
int ft_ispunct(int c);
int ft_isspace(int c);
int ft_isupper(int c);
int ft_isxdigit(int c);
int ft_isascii(int c);
int ft_isblank(int c);
int	isunicode(wchar_t c);

#endif
