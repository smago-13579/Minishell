# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smago <smago@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 21:49:45 by smago             #+#    #+#              #
#    Updated: 2020/12/28 21:33:37 by smago            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

LIBDR = libft/

SRCS = main.c ft_prompt.c ft_init.c ft_parse.c ft_new_buff.c ft_fill_tokens.c \
		ft_free_all.c ft_lexical_logical.c ft_variable_env.c ft_redirect.c \
		ft_error.c ft_exe_cmd.c ft_exe_cmd2.c ft_pipe.c ft_exit_code.c

OBJ = $(SRCS:%.c=%.o)

# for esnowbal
SRCS2 = command_me.c change_dir.c env_update.c echo_env_pwd.c exp_add_newkey.c \
			exp_utils.c exp_free_create.c gnl.c exp_pwd_or_oldpwd.c

OBJ2 = $(SRCS2:%.c=%.o)
# for esnowbal

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(OBJ2) $(LIBFT) minishell.h
	gcc $(FLAGS) $(OBJ) $(OBJ2) $(LIBFT) -o $(NAME)

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

$(LIBFT): $(LIBDR)*.c $(LIBDR)libft.h
	make -C $(LIBDR)

clean:
	make -C $(LIBDR) clean
	rm -f $(OBJ) $(OBJ2)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

