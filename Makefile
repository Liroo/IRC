##
## Makefile<IRC> for IRC in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:42 2017 Pierre Monge
## Last update Mon Jun 12 16:50:11 2017 Pierre Monge
##

PROJECT := IRC

SERVER = ./irc_server
SERVER_BIN = server
CLIENT = ./irc_client
CLIENT_BIN = client
CP = cp
RM = rm -f

all:
	@make --no-print-directory $(SERVER_BIN)
	@make --no-print-directory $(CLIENT_BIN)

$(SERVER_BIN):
	@make --no-print-directory -C $(SERVER)
	@$(CP) $(SERVER)/$(SERVER_BIN) .

$(CLIENT_BIN):
	@make --no-print-directory -C $(CLIENT)
	@$(CP) $(CLIENT)/$(CLIENT_BIN) .

debug:
	@make --no-print-directory -C $(SERVER_BIN) debug
	@make --no-print-directory -C $(CLIENT_BIN) debug

clean:
	@make --no-print-directory -C $(SERVER) clean
	@make --no-print-directory -C $(CLIENT) clean

fclean:
	@make --no-print-directory -C $(SERVER) fclean
	@make --no-print-directory -C $(CLIENT) fclean
	$(RM) $(SERVER_BIN)
	$(RM) $(CLIENT_BIN)

re: fclean all

.PHONY: debug
