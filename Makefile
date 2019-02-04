# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2019/02/04 16:21:55 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all tags

SRCDIR= src/

vpath %.c $(SRCDIR)
vpath %.h includes/

CFLAGS= -Wall -Wextra -Werror $(INCLUDE)
DEBUG=prod
OPT=LIB
ARCH:= $(shell uname)

ifeq ($(ARCH), Darwin)
	CC= clang
else ifeq ($(ARCH), Linux)
	CC=gcc-8
	CFLAGS+= -fPIC
endif

ifeq ($(DEBUG), yes)
	CFLAGS+= -g3
else ifeq ($(DEBUG), prod)
	CFLAGS+= -O3 -DNDEBUG
else ifeq ($(DEBUG), sanitize)
	CFLAGS+= -g3 -fsanitize=address
endif

INCLUDE=\
-Iincludes\
-I$(LIBDIR)bridge\
-I$(LIBDIR)is\
-I$(LIBDIR)buf\
-I$(LIBDIR)mem\
-I$(LIBDIR)maths\

HEADERS= malloc.h\

SRC= malloc.c\
	 extract.c\
	 defragment.c\
	 large.c\
	 macro_0.c\
	 macro_1.c\
	 macro_2.c\
	 free.c\
	 show.c\
	 track.c\
	 xalloc.c\
	 sort.c\
	 dump.c\

OBJDIR= obj
OBJ= $(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))

LIBDIR= libft/
LIB= libft.a

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= libft_malloc_$(HOSTTYPE).so
SYMLINK=libft_malloc.so

GREEN="\033[32m"
RESET="\033[0m"


all: $(LIB) $(NAME)

$(NAME): $(LIBDIR)$(LIB) $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJ) -L$(LIBDIR) -lft
	@echo $(GREEN)$(NAME)" Successfully created"$(RESET)
	@ln -fs $(NAME) $(SYMLINK)

exec:  $(NAME) $(LIBDIR)$(LIB) $(OBJ)
	$(CC) $(CFLAGS) -o exec $(OBJ) -L$(LIBDIR) -lft
	@echo $(GREEN)" exec Successfully created"$(RESET)

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(COMPILE.c) $< -o $@ $(INCLUDE)

$(OBJDIR):
	-mkdir -p $@

$(LIB):
	@$(MAKE) -C $(LIBDIR)

$(LIBDIR)$(LIB):
	@$(MAKE) -C $(LIBDIR)

main: $(LIB)
	$(CC) $(CFLAGS) -o test $(main) -L$(LIBDIR) -lft
	-rm -f $(main:.c=.o)

tags:
	ctags -R *

clean:

ifeq ($(OPT), LIB)
	@$(MAKE) clean -C $(LIBDIR)
endif
	$(RM) -r $(OBJDIR) 
	@$(RM) test a.out
	@$(RM) -r test.dSYM

fclean: clean

ifeq ($(OPT), LIB)
	@$(MAKE) fclean -C $(LIBDIR)
endif		
	$(RM) $(NAME) $(SYMLINK)
	@$(RM) -r $(NAME).dSYM

re : fclean all
