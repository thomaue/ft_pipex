# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tauer <tauer@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 17:59:50 by tauer             #+#    #+#              #
#    Updated: 2024/02/28 18:51:23 by tauer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	=	src
BUILD_DIR	=	build
NAME		=	pipex
CFLAG		=	-Wall -Wextra -Werror -I./header -g3

SRC			=\
			$(wildcard $(SRC_DIR)/*.c)
CC			=	cc

OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRC))

ARGV    = file1.txt cat ls file2.txt

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC)	$(CFLAG)	-c	$< -o	$@
	@clear
	
all: $(NAME)

$(NAME):$(OBJ)
	@echo $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(CFLAG)
	@clear


clear :
	@clear
	@echo "42Paris : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@rm *.txt
	@echo "Clean   : *.o in build !"

fclean : clean
	@rm -f $(NAME)
	@echo "Clean   : ./$(NAME)"

pip :
	@ echo "./"$(NAME) $(ARGV)
	@ touch file1.txt
	@ ./$(NAME) $(ARGV)
	

valgrind : clear
	@touch file1.txt
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./$(NAME) $(ARGV)

re: fclean all clear 
	touch file1.txt

.PHONY: all clean fclean re
