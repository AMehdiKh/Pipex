###############################################################################################################
NAME = pipex

BNAME = pipex_bonus
###############################################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD
###############################################################################################################
MANDIR = Mandatory

OBJDIR = Mandatory/objs

FILES = main parse_cmd utils_I utils_II

SRCS = $(addsuffix .c,$(FILES))

OBJS = ${SRCS:%.c=$(OBJDIR)/%.o}

MANDEP = ${OBJS:.o=.d}
##############################################################################################################
BONDIR = Bonus

BOBJDIR = Bonus/objs

BFILES = main parse_cmd utils_I utils_II

BSRCS = $(addsuffix _bonus.c,$(BFILES))

BOBJS = ${BSRCS:%.c=$(BOBJDIR)/%.o}

BONDEP = ${BOBJS:.o=.d}
##############################################################################################################
LIBFT = LibFT/libft.a
##############################################################################################################
.PHONY: clean
man: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $@

$(OBJDIR)/%.o: $(MANDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BNAME)
$(BNAME): $(LIBFT) $(BOBJS)
	$(CC) $(BOBJS) $(LIBFT) -o $@

$(BOBJDIR)/%.o: $(BONDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: man bonus

$(LIBFT):
	$(MAKE) -C LibFT

sinclude $(MANDEP) $(BONDEP)

clean:
	$(MAKE) fclean -C LibFT
	$(RM) -r $(OBJDIR) $(BOBJDIR)

fclean: clean
	$(RM) $(NAME) $(BNAME)

re: fclean all
