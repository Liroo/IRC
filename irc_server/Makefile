##
## Makefile<irc_server> for IRC_SERVER in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:36 2017 Pierre Monge
## Last update Sun Jun 11 07:39:34 2017 Pierre Monge
##


PROJECT := IRC_SERVER

OBJ_DIR := obj/

# General behavior

NAME_BIN := server

SRC_GENDIR := src/
OBJ_GENDIR := $(OBJ_DIR)src/

SRC_GEN = \
	irc_server.c \
	\
	socket.c \
	fd_list.c \
	sig.c \
	event.c \
	list.c \
	ring_buffer.c \
	parse.c \
	command.c \
	hash.c \
	client_write.c \
	channel.c \
	\
	commands/c_nick.c \
	commands/c_quit.c \
	commands/c_ping.c \
	commands/c_user.c \
	commands/c_users.c \
	commands/c_privmsg.c

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.c=.o))

# Utility

INCDIRS := -I./include

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
