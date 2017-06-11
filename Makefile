##
## Makefile<IRC> for IRC in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:42 2017 Pierre Monge
## Last update Sun Jun 11 20:44:53 2017 Pierre Monge
##

PROJECT := IRC

SERVER = ./irc_server
SERVER_BIN = server
CLIENT = ./irc_client
CLIENT_BIN = client
CP = cp
RM = rm -f

all:
	@make --no-print-directory -C $(SERVER)
	@make --no-print-directory -C $(CLIENT)
	$(CP) $(SERVER)/$(SERVER_BIN) .
	$(CP) $(CLIENT)/$(CLIENT_BIN) .

server:
	@make --no-print-directory -C $(SERVER)

client:
	@make --no-print-directory -C $(CLIENT)

debug:
	@make --no-print-directory -C $(SERVER) debug
	@make --no-print-directory -C $(CLIENT) debug
	$(CP) $(SERVER)/$(SERVER_BIN) .
	$(CP) $(CLIENT)/$(CLIENT_BIN) .

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
