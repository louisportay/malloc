BRIDGE=\
	ft_atol.c\
	width.c\
	ltoa.c\
	ft_abs.c\
	swap.c\

BRIDGE_DIR=bridge

OBJ+=$(addprefix $(OBJDIR)/$(BRIDGE_DIR)/, $(BRIDGE:%.c=%.o))

SRCDIR+=$(BRIDGE_DIR)/

INCLUDE+=-I$(BRIDGE_DIR)/

HEADER=bridge

$(OBJDIR)/$(BRIDGE_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(BRIDGE_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(BRIDGE_DIR):
	mkdir -p $(OBJDIR)/$(BRIDGE_DIR)
