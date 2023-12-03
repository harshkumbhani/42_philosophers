# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: harsh <harsh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 12:24:11 by harsh             #+#    #+#              #
#    Updated: 2023/12/01 12:25:42 by harsh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- Config ---------------------------------- #
NAME				:= philo
CC					:= cc
CFLAGS				:=  -I./includes -g -Wall -Wextra -Werror

# --------------------------- Program Source files --------------------------- #
OBJDIR				:= ./objs
VPATH				:= ./src/

SRC					:= main.c

SRCS				:= $(SRC)

OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

# ----------------------------------- Rules ---------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -pthread -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -rf objs

fclean: clean
	@rm -f $(NAME)

norm: $(SRCS)
	$(shell norminette | grep Error)

re: fclean all

.PHONY: all clean fclean re