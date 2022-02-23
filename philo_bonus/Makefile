NAME		=	philo_bonus

HEAD		=	philo_bonus.h

SRCS		=	philo_bonus.c handling_errors.c create_info.c\
				create_process.c utils.c actions.c free_destroy.c

OBJS		=	$(SRCS:.c=.o)
				
CC			=	gcc 
CFLAGS		=	-Wall -Wextra -Werror -pthread -I $(HEAD)

.PHONY		:	all clean fclean re

all			:	$(NAME)

%.o:			%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) 	:	$(OBJS) $(HEAD)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:	
	@rm -f $(OBJS) $(OBJS_B)

fclean		:	clean
	@rm -f $(NAME) $(NAME_B)

re:			fclean all