PRINTF = libftprintf.a

NAME = pipex

SRC_DIR = sources

PRINTF_DIR = includes/ft_printf

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c

FLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME): $(PRINTF)
	@ $(CC) $(FLAGS) $(PRINTF) $(SRC) -o $(NAME)

$(PRINTF):
	@ $(MAKE) re -sC $(PRINTF_DIR) 
	@ cp $(PRINTF_DIR)/$(PRINTF) .

all : $(NAME)

clean:
	@ $(MAKE) clean -C $(PRINTF_DIR)
	@ $(RM) $(PRINTF)

fclean: clean
	@ $(MAKE) fclean -C $(PRINTF_DIR)
	@ $(RM) $(PRINTF)
	@ $(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
