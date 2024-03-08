NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = main.c utils.c ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c get_next_line.c get_next_line_utils.c

all:
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY = all clean fclean re