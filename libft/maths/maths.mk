MAT=\
	uround.c\

MAT_DIR=maths

OBJ+=$(addprefix $(OBJDIR)/$(MAT_DIR)/, $(MAT:%.c=%.o))

SRCDIR+=$(MAT_DIR)/

INCLUDE+=-I$(MAT_DIR)/

HEADER=maths

$(OBJDIR)/$(MAT_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(MAT_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(MAT_DIR):
	mkdir -p $(OBJDIR)/$(MAT_DIR)
