# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 13:37:28 by myli-pen          #+#    #+#              #
#    Updated: 2025/09/17 22:11:34 by myli-pen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=minishell

CC			:=cc
CFLAGS		:=-Wall -Wextra -Werror -Wunreachable-code -O3 -march=native -funroll-loops -fno-plt
LDFLAGS		:=-lreadline -flto
MAKEFLAGS	+= --no-print-directory

DIR_INC		:=inc/
DIR_SRC		:=src/
DIR_LIB		:=lib/
DIR_OBJ		:=obj/
DIR_DEP		:=dep/
DIR_EXE		:=executor/
DIR_PAR		:=parser/

DIR_LIBFT	:=$(DIR_LIB)libft/
LIBFT		:=$(DIR_LIBFT)libft.a

INCS		:=$(addprefix -I, \
				$(DIR_INC) $(DIR_INC)$(DIR_EXE) $(DIR_INC)$(DIR_PAR) $(DIR_LIBFT)$(DIR_INC))

SRCS		:=$(addprefix $(DIR_SRC), \
				main.c)

SRCS_EXE	:=$(addprefix $(DIR_SRC)$(DIR_EXE), \
				unset.c)

SRCS_PAR	:=$(addprefix $(DIR_SRC)$(DIR_PAR), \
				parsing.c mem_arena.c)

OBJS		:=$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SRCS))
OBJS		+=$(patsubst $(DIR_SRC)$(DIR_EXE)%.c, $(DIR_OBJ)$(DIR_EXE)%.o, $(SRCS_EXE))
OBJS		+=$(patsubst $(DIR_SRC)$(DIR_PAR)%.c, $(DIR_OBJ)$(DIR_PAR)%.o, $(SRCS_PAR))

DEPS		:=$(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $(OBJS))

BLUE		:=\033[1;34m
YELLOW		:=\033[1;33m
GREEN		:=\033[1;32m
RED			:=\033[1;31m
COLOR		:=\033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(GREEN) [+]$(COLOR) compiling libft.a"
	@+make -C $(DIR_LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(YELLOW) [✔] $(NAME) created$(COLOR)"

$(OBJS): $(LIBFT)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@) $(patsubst $(DIR_OBJ)%, $(DIR_DEP)%, $(dir $@))
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $@) $(INCS)
	@echo "$(GREEN) [+]$(COLOR) compiling $@"

clean:
	@if [ -d "$(DIR_OBJ)" ]; then \
		rm -rf $(DIR_OBJ); \
		echo "$(RED) [-]$(COLOR) removed $(DIR_OBJ)"; \
	fi
	@+make -C $(DIR_LIBFT) clean

fclean: clean
	@+make -C $(DIR_LIBFT) fclean
	@if [ -d "$(DIR_DEP)" ]; then \
		rm -rf $(DIR_DEP); \
		echo "$(RED) [-]$(COLOR) removed $(DIR_DEP)"; \
	fi
	@if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED) [-]$(COLOR) removed $(NAME)"; \
	fi

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS) $(DEPS)

-include $(DEPS)
