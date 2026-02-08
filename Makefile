CC := gcc
CFLAGS := -Wall -Wextra

OBJDIR := build
BINDIR := bin

OBJS := $(OBJDIR)/main.o \
        $(OBJDIR)/llist.o \
        $(OBJDIR)/node.o \
        $(OBJDIR)/address.o \
        $(OBJDIR)/util.o

$(BINDIR)/main: $(OBJS) | $(BINDIR)
	$(CC) $(OBJS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
