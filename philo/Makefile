NAME		=	philo

SRCS		=	main.c ft_atoi.c utils.c init.c end.c actions.c

OBJS		=	$(SRCS:.c=.o)
				
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -lpthread

.PHONY		:	all clean fclean re

all			:	$(NAME)

%.o:			%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) 	:	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LNK) -lm -o $(NAME)

clean		:	
	@rm -f $(OBJS) $(OBJS_B)

fclean		:	clean
	@rm -f $(NAME) $(NAME_B)

re:			fclean all