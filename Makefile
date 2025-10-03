# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 13:37:28 by myli-pen          #+#    #+#              #
#    Updated: 2025/10/03 06:45:35 by myli-pen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=minishell

POOL_SIZE	?= 1048576
CONF		:=.config

WARNS		:=-Wall -Wextra -Werror -Wunreachable-code
DEFS		:=-D POOL_SIZE=$(POOL_SIZE)
OPTS		:=-O3 -march=native -funroll-loops -fno-plt
CC			:=cc
CFLAGS		:=$(WARNS) $(DEFS) $(OPTS)
LDFLAGS		:=-flto
LIBS		:=-lreadline

MAKEFLAGS	+= --no-print-directory

DIR_INC		:=inc/
DIR_SRC		:=src/
DIR_LIB		:=lib/
DIR_OBJ		:=obj/
DIR_DEP		:=dep/

DIR_BUILT	:=builtin/
DIR_ENV		:=env/
DIR_EXE		:=executor/
DIR_LEX		:=lexer/
DIR_PAR		:=parser/
DIR_UTILS	:=utils/

DIR_LIBFT	:=$(DIR_LIB)libft/
LIBFT		:=$(DIR_LIBFT)libft.a

INCS		:=$(addprefix -I, \
				$(DIR_LIBFT)$(DIR_INC)\
				$(DIR_INC) \
				$(DIR_INC)$(DIR_BUILT) \
				$(DIR_INC)$(DIR_ENV) \
				$(DIR_INC)$(DIR_EXE) \
				$(DIR_INC)$(DIR_LEX) \
				$(DIR_INC)$(DIR_PAR) \
				$(DIR_INC)$(DIR_UTILS) \
				)

SRCS		:=$(addprefix $(DIR_SRC), \
				main.c \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_BUILT), \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIRDIR_ENV_EXE), \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_EXE), \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_LEX), \
				lexer_utils.c \
				lexer.c \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_PAR), \
				expansion.c \
				parser.c \
				redirection.c \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_UTILS), \
				arena_utils.c \
				arena_list.c \
				arena.c \
				defines.c \
				errors.c \
				str_utils.c \
				str_split.c \
				str_split_utils.c \
				)
OBJS		:=$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SRCS))
DEPS		:=$(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $(OBJS))

BLUE		:=\033[1;34m
YELLOW		:=\033[1;33m
GREEN		:=\033[1;32m
RED			:=\033[1;31m
COLOR		:=\033[0m

all: $(LIBFT) config $(NAME)

$(LIBFT):
	@echo "$(GREEN) [+]$(COLOR) compiling libft.a"
	@make -j4 -C $(DIR_LIBFT)

config:
	@if [ ! -e "$(CONF)" ] || [ "$$(cat "$(CONF)")" != "$(POOL_SIZE)" ]; then \
		echo "$(POOL_SIZE)" > "$(CONF)"; \
	fi

$(NAME): $(OBJS) $(LIBFT) $(CONF)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LIBFT)
	@if [ $$(($(POOL_SIZE)/1024/1024)) -lt 1 ]; then \
		echo "$(YELLOW) [✔] $(NAME) built with $(POOL_SIZE) KiB memory$(COLOR)"; \
	else \
		echo "$(YELLOW) [✔] $(NAME) built with $$(echo "scale=1; $(POOL_SIZE)/1024/1024" | bc) MiB memory$(COLOR)"; \
	fi

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(LIBFT) $(CONF)
	@mkdir -p $(dir $@) $(patsubst $(DIR_OBJ)%, $(DIR_DEP)%, $(dir $@))
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $@) $(INCS)
	@echo "$(GREEN) [+]$(COLOR) compiling $@"

clean:
	@if [ -d "$(DIR_OBJ)" ]; then \
		rm -rf $(DIR_OBJ); \
		echo "$(RED) [-]$(COLOR) removed $(DIR_OBJ)"; \
	fi
	@make -j4 -C $(DIR_LIBFT) clean

fclean: clean
	@make -j4 -C $(DIR_LIBFT) fclean
	@if [ -d "$(DIR_DEP)" ]; then \
		rm -rf $(DIR_DEP); \
		echo "$(RED) [-]$(COLOR) removed $(DIR_DEP)"; \
	fi
	@if [ -e "$(CONF)" ]; then \
		rm -f $(CONF); \
		echo "$(RED) [-]$(COLOR) removed $(CONF)"; \
	fi
	@if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED) [-]$(COLOR) removed $(NAME)"; \
	fi

re: fclean all

.PHONY: all clean fclean re config
.SECONDARY: $(OBJS) $(DEPS) $(CONF)

-include $(DEPS)
