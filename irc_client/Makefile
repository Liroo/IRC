##
## Makefile<irc_client> for IRC_CLIENT in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:26 2017 Pierre Monge
## Last update Sat May 27 06:31:03 2017 Pierre Monge
##

PROJECT := IRC_CLIENT

OBJ_DIR := obj/

# General behavior

NAME_BIN := client

SRC_GENDIR := src/
OBJ_GENDIR := $(OBJ_DIR)src/

SRC_GEN = \
	main.c

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.c=.o))

# Utility

INCDIRS := -I./src

CC = gcc

FLAGS = -W -Werror -Wextra -Wall
# if debug is activated
FLAGS += $(DEBUG)
FLAGS += -D _GNU_SOURCE

CFLAGS = $(FLAGS) $(INCDIRS)

RM		:= rm -rf

# Rules

all:
	@make --no-print-directory $(NAME_BIN)

# debug: FLAGS += -DDEBUG -g
debug: fclean
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG -g'

$(OBJ_GENDIR)%.o: $(SRC_GENDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(ERRLOG)

$(NAME_BIN): $(NAME_LIB) $(OBJ_GEN)
	$(CC) -o $(NAME_BIN) $(OBJ_GEN) $(CFLAGS)

clean:
	@$(RM) $(LOGFILE)
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME_BIN)

re: fclean all

.PHONY: debug
