NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = main.c utils.c parse_cmd.c ft_split.c ft_split_quotes.c ft_strjoin.c ft_strdup.c ft_strncmp.c ft_strlen.c ft_putstr_fd.c \
		ft_strnstr.c ft_substr.c gnl.c gnl_utils.c

all:
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY = all clean fclean re