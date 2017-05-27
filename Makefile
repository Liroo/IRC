##
## Makefile<IRC> for IRC in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:42 2017 Pierre Monge
## Last update Sat May 27 06:36:37 2017 Pierre Monge
##

PROJECT := IRC

SERVER = ./irc_server
CLIENT = ./irc_client
BUILD_SCRIPT = ./install.sh

.NOTPARALLEL:

all:
	@make --no-print-directory -C $(SERVER)
	@make --no-print-directory -C $(CLIENT)
	@$(BUILD_SCRIPT) install `pwd`

server:
	@make --no-print-directory -C $(SERVER)

client:
	@make --no-print-directory -C $(CLIENT)

debug:
	@make --no-print-directory -C $(SERVER) debug
	@make --no-print-directory -C $(CLIENT) debug

clean:
	@make --no-print-directory -C $(SERVER) clean
	@make --no-print-directory -C $(CLIENT) clean

fclean:
	@make --no-print-directory -C $(SERVER) fclean
	@make --no-print-directory -C $(CLIENT) fclean
	@$(BUILD_SCRIPT) uninstall `pwd`

re: fclean all

.PHONY: debug
