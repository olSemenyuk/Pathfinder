NAME := pathfinder
COMP := clang
CFLG := -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCD := src
INCD := inc
OBJD := obj
LMXD := Libmx
LMXA := $(LMXD)/libmx.a
LMXI := $(LMXD)/inc

INCS := $(INCD)/pathfinder.h $(LMXI)/libmx.h
SRC := \
	main.c \
	file_does_not_exist.c \
	file_is_empty.c \
	ivalid_usage.c \
	line1_is_not_valid.c \
	mx_parser.c \
	mx_pars_str.c \
	duplicate_bridges.c \
	printerr_line.c \
	error_dup1.c \
	mx_create_matrix_dist.c \
	mx_create_matrix_floyd.c \
	mx_get_index.c \
	mx_floyd.c \
	mx_find_all_path.c \
	mx_back_path.c \
	mx_output.c \
	mx_int_print.c

OBJS := $(addprefix $(OBJD)/, $(SRC:.c=.o))

.PHONY: all install clean uninstall reinstall

all: $(NAME)

install: all

$(NAME): $(OBJS) $(LMXA)
	@$(COMP) $(CFLG) $(OBJS) -L$(LMXD) -lmx -o $@
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(COMP) $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LMXA): $(wildcard $(LMXD)/src/*.c) $(LMXD)/inc/libmx.h $(LMXD)/Makefile
	@$(MAKE) -sC $(LMXD)

clean:
	@$(MAKE) -sC $(LMXD) clean
	@rm -rf $(OBJD) $(NAME)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(MAKE) -sC $(LMXD) uninstall

reinstall:
	@$(MAKE) uninstall
	@$(MAKE) all
