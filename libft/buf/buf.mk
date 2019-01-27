BUF=\
	buf_c.c\
	buf_wc.c\
	buf_l.c\
	buf_utils.c\

BUF_DIR=buf

OBJ+=$(addprefix $(OBJDIR)/$(BUF_DIR)/, $(BUF:%.c=%.o))

SRCDIR+=$(BUF_DIR)/

INCLUDE+=-I$(BUF_DIR)/

HEADER=buf

$(OBJDIR)/$(BUF_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(BUF_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(BUF_DIR):
	mkdir -p $(OBJDIR)/$(BUF_DIR)
