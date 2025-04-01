NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

INC = -Iincludes

SRCFOLDER = src/

OBJFOLDER = objs/

SRC_LIST = utils.c		\
	free.c				\
	init_rules.c		\
	init_philo.c		\
	mutex_functions.c	\
	mutex_functions_2.c	\
	launchs.c			\
	routine.c			\
	main.c				\
	

SRC = $(addprefix $(SRCFOLDER), $(SRC_LIST))

SRC_OBJS = $(patsubst $(SRCFOLDER)%.c, $(OBJFOLDER)%.o, $(SRC))

all : $(NAME)

$(NAME) : $(SRC_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $@

$(OBJFOLDER)%.o : $(SRCFOLDER)%.c Makefile includes/*
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean: 
	@rm -rf $(OBJFOLDER)

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
