NAME := connect4

# Directories
SRCDIR := src
INCDIR := include
LIBDIR := lib
BINDIR := build

# Files
SRCS := main
BINS := $(SRCS:%=$(BINDIR)/%.o)

# Libraries
LIBFTDIR := $(LIBDIR)/libft
LIBFT := $(LIBFTDIR)/libft.a

# Compilation
CC := cc
CFLAGS := -Wall -Wextra -Werror
debug: CFLAGS += -ggdb3 -Og
CPPFLAGS := -I$(INCDIR) -I$(LIBFTDIR)/include
LDFLAGS := -L$(LIBFTDIR)

# Colors
COLOUR_END := \033[0m
COLOUR_GREEN := \033[0;32m
COLOUR_RED := \033[0;31m
COLOUR_MAG := \033[0;35m
COLOUR_MAGB := \033[1;35m
COLOUR_CYN := \033[0;36m
COLOUR_CYNB := \033[1;36m

MKDIR := mkdir -p

# Rules
.PHONY: all bonus clean debug fclean re

all: $(NAME) # Build all

$(NAME): $(LIBFT) $(BINS)
	$(CC) $(CPPFLAGS) $(BINS) -o $(NAME)

$(BINS): $(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c $^ -o $@

$(BINDIR):
	$(MKDIR) $(BINDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) $(MAKECMDGOALS)

bonus: # Build bonus

clean: # Remove compiled binary objects
	$(RM) -fr $(BINDIR)

fclean: clean # Remove all compiled binaries and libraries
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) $(MAKECMDGOALS)

re: fclean all # Recompile all

help: # Display this helpful message
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\t$(COLOUR_CYNB)make $(COLOUR_MAGB)<target> \
	$(COLOUR_END)\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "$(COLOUR_MAGB)%-16s$(COLOUR_CYN)%s$(COLOUR_END)\n", $$1, $$2 } ' \
	Makefile
