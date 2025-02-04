CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFTPRINTF = ft_printf/libftprintf.a
INCLUDES = -I./ft_printf -I./ft_printf/libft

SRCS_SERVER = server.c utils.c ft_printf/ft_printf.c ft_printf/fonction_format.c ft_printf/fonction_format2.c ft_printf/ft_memset.c ft_printf/ft_atoi.c
SRCS_CLIENT = client.c utils.c ft_printf/ft_printf.c ft_printf/fonction_format.c ft_printf/fonction_format2.c ft_printf/ft_memset.c ft_printf/ft_atoi.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: server client


$(LIBFTPRINTF): $(LIBFT)
	$(MAKE) -C ft_printf

server: $(OBJS_SERVER) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFTPRINTF) -o server

client: $(OBJS_CLIENT) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFTPRINTF) -o client

clean:
	$(MAKE) -C ft_printf/libft clean
	$(MAKE) -C ft_printf clean
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(MAKE) -C ft_printf/libft fclean
	$(MAKE) -C ft_printf fclean
	rm -f server client

re: fclean all

.PHONY: all clean fclean re