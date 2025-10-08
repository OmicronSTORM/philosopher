# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 16:36:17 by jowoundi          #+#    #+#              #
#    Updated: 2025/10/08 14:43:36 by jowoundi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread -g3
GREEN   = "\\033[32m"
YELLOW	= "\\033[33m"
NC      = "\\033[0m"

INCLUDES = -I ./header

SRC_DIR = src/
OBJ_DIR = obj/

# Source files from the src directory
SRCS = main.c fill_data.c utils.c parsing.c init_philo.c routine.c print_message.c

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0

define progress_bar
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "\r$(YELLOW)Compiling push_swap... [%-$(TOTAL_FILES)s] %d/%d $(NC)" \
	$$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES)  ]; then echo ""; fi
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call progress_bar)


LOGO = "\033[5;36m\
█▀▀▄   ▄  █ █▄ █    ████▄ \n \
█   █ █   █  █ █    █   █ \n \
█▀▀▀  ██▀▀█  █ █    █   █ \n \
█     █   █  █ ███▄ ▀████ \n \
▀█           ▐     ▀      \n \
  ▀     ▀                 \n \
\033[6;36m"


all:  $(NAME)

$(NAME): $(OBJS)
	@printf "\n"
	@printf $(LOGO)
	@echo "Linking objects to create executable..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Executable $(NAME) created!"

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re