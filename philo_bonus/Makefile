NAME		=	philo_bonus

SRCS		=	ft_atoi.c philo_bonus.c handling_errors.c create_info.c\
				create_threads.c utils.c actions.c free_destroy.c

OBJS		=	$(SRCS:.c=.o)
				
CC			=	gcc 
CFLAGS		=	-Wall -Wextra -Werror -g -pthread

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