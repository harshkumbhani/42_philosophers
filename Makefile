# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:30:19 by hkumbhan          #+#    #+#              #
#    Updated: 2024/01/02 10:28:08 by hkumbhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- Config ---------------------------------- #
NAME				:= philo
CC					:= cc
CFLAGS				:=  -I./includes -g # -Wall -Wextra -Werror

# --------------------------- Program Source files --------------------------- #
OBJDIR				:= ./objs
VPATH				:= ./src/

SRC					:= main.c time.c

SRCS				:= $(SRC)

OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

# ----------------------------------- Rules ---------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $@

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