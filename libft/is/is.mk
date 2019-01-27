IS=\
   ft_isalnum.c\
   ft_isalpha.c\
   ft_isascii.c\
   ft_isblank.c\
   ft_iscntrl.c\
   ft_isdigit.c\
   ft_isgraph.c\
   ft_islower.c\
   ft_isprint.c\
   ft_ispunct.c\
   ft_isspace.c\
   ft_isupper.c\
   ft_isxdigit.c\
   isunicode.c\

IS_DIR=is

OBJ+=$(addprefix $(OBJDIR)/$(IS_DIR)/, $(IS:%.c=%.o))

SRCDIR+=$(IS_DIR)/

INCLUDE+=-I$(IS_DIR)/

HEADER=is

$(OBJDIR)/$(IS_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(IS_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(IS_DIR):
	mkdir -p $(OBJDIR)/$(IS_DIR)
