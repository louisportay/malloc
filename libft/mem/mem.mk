MEM=\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\

MEM_DIR=mem

OBJ+=$(addprefix $(OBJDIR)/$(MEM_DIR)/, $(MEM:%.c=%.o))

SRCDIR+=$(MEM_DIR)/

INCLUDE+=-I$(MEM_DIR)/

HEADER=mem

$(OBJDIR)/$(MEM_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(MEM_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(MEM_DIR):
	mkdir -p $(OBJDIR)/$(MEM_DIR)
