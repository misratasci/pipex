NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = main.c utils.c parse_cmd.c ft_split.c ft_strjoin.c ft_strdup.c ft_strncmp.c ft_strlen.c gnl.c gnl_utils.c

all:
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY = all clean fclean re