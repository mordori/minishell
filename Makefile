# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 13:37:28 by myli-pen          #+#    #+#              #
#    Updated: 2025/10/07 20:46:57 by myli-pen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=minishell

MEMORY		?=1048576
CONF		:=.config

WARNS		:=-Wall -Wextra -Werror -Wunreachable-code
DEFS		:=-D MEMORY=$(MEMORY)
DFLAGS		:=-D DEBUG -g
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
				$(DIR_INC)$(DIR_UTILS) \
				)

SRCS		:=$(addprefix $(DIR_SRC), \
				main.c)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_BUILT), \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_ENV), \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_EXE), \
				 \
				)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_LEX), \
				lexer_utils.c \
				lexer.c \
				str_split_utils.c \
				str_split.c)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_PAR), \
				expansion.c \
				parser.c \
				io.c)
SRCS		+=$(addprefix $(DIR_SRC)$(DIR_UTILS), \
				arena_list.c \
				arena_utils.c \
				arena.c \
				cleanup.c \
				defines.c \
				errors.c \
				str_utils.c \
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
	@$(call check_config,NORMAL)

$(NAME): $(OBJS) $(LIBFT) $(CONF)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LIBFT)
	@$(call output)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(LIBFT) $(CONF)
	@mkdir -p $(dir $@) $(patsubst $(DIR_OBJ)%, $(DIR_DEP)%, $(dir $@))
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $@) $(INCS)
	@echo "$(GREEN) [+]$(COLOR) compiling $@"

clean:
	@make -j4 -C $(DIR_LIBFT) clean
	@$(call rm_dir,$(DIR_OBJ))

fclean: clean
	@make -j4 -C $(DIR_LIBFT) fclean
	@$(call rm_dir,$(DIR_DEP))
	@$(call rm_file,$(CONF))
	@$(call rm_file,$(NAME))

re: fclean all

debug: CFLAGS := $(WARNS) $(DEFS) $(DFLAGS) -O0
debug: $(LIBFT) config_debug $(NAME)

config_debug:
	@$(call check_config,DEBUG)

.PHONY: all clean fclean re config debug config_debug
.SECONDARY: $(OBJS) $(DEPS) $(CONF)

-include $(DEPS)

define rm_dir
	@if [ -d "$(1)" ]; then \
		rm -rf $(1); \
		echo "$(RED) [-]$(COLOR) removed $(1)"; \
	fi
endef

define rm_file
	@if [ -e "$(1)" ]; then \
		rm -f $(1); \
		echo "$(RED) [-]$(COLOR) removed $(1)"; \
	fi
endef

define check_config
	@if [ ! -e "$(CONF)" ]; then \
		touch "$(CONF)"; \
		echo "" >> $(CONF); \
		echo "" >> $(CONF); \
	fi
	@if [ "$$(head -n 1 $(CONF))" != "$(1)" ]; then \
		sed -i '1c\$(1)' "$(CONF)"; \
	fi
	@if [ "$$(head -n 2 $(CONF) | tail -n 1)" != "$(MEMORY)" ]; then \
		sed -i '2c\$(MEMORY)' "$(CONF)"; \
	fi
endef

define output
	@if [ $$(($(MEMORY))) -lt 1024 ]; then \
		echo "$(YELLOW) [✔] $(NAME) built with invalid amount of memory (1 KiB is minimum)$(COLOR)"; \
		echo "$(RED) [/] the program will throw an error if run$(COLOR)"; \
	elif [ $$(($(MEMORY) & ($(MEMORY) - 1))) -ne 0 ]; then \
		echo "$(YELLOW) [✔] $(NAME) built with non power of two amount of memory$(COLOR)"; \
		echo "$(RED) [/] the program will throw an error if run$(COLOR)"; \
	elif [ $$(($(MEMORY)/1024/1024)) -lt 1 ]; then \
		echo "$(YELLOW) [✔] $(NAME) built with $$(echo "scale=1; $(MEMORY)/1024" | bc) KiB memory$(COLOR)"; \
	elif [ $$(($(MEMORY)/1024/1024)) -lt 1000 ]; then \
		echo "$(YELLOW) [✔] $(NAME) built with $$(echo "scale=1; $(MEMORY)/1024/1024" | bc) MiB memory$(COLOR)"; \
	else \
		echo "$(YELLOW) [✔] $(NAME) built with $$(echo "scale=1; $(MEMORY)/1024/1024/1024" | bc) GiB memory$(COLOR)"; \
	fi
	@if [ $$(($(MEMORY))) -gt 1023 ] && [ $$(($(MEMORY) & ($(MEMORY) - 1))) -eq 0 ]; then \
		echo "$(GREEN) [/] usage: ./$(NAME)$(COLOR)"; \
	fi
	@if [ "$$(head -n 1 $(CONF))" != "NORMAL" ]; then \
		echo "$(YELLOW) [DEBUG MODE]$(COLOR)"; \
	fi
endef
