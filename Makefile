# -- Compiler options -------------------------------------------
CC:=cc
CFLAGS:=-Wall -Wextra -Werror
#CFLAGS+=-g
DFLAGS:= -MMD -MP -MF

# -- Directories ------------------------------------------------
IDIR:=include
ODIR:=obj
SDIR:=src
DDIR:=dep

CFLAGS+=-I$(IDIR)

# -- Files ------------------------------------------------------
SRC:=main.c
OBJ:=$(addprefix $(ODIR)/, $(SRC:.c=.o))
DEP:=$(addprefix $(DDIR)/, $(OBJ:.o=.d))
NAME:= phil

# -- Rules ------------------------------------------------------
all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(patsubst $(SDIR)/%.c, $(DDIR)/%.d, $<) -c $< -o $@

-include $(DEP)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(ODIR) $(DDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
