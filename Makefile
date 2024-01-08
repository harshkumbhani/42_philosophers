# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 12:24:11 by harsh             #+#    #+#              #
#    Updated: 2024/01/08 13:46:27 by hkumbhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- Config ---------------------------------- #
NAME				:= philo
CC					:= cc #-fsanitize=thread
CFLAGS				:= -I./includes -g #-Wall -Wextra -Werror

# --------------------------- Program Source files --------------------------- #
OBJDIR				:= ./objs
VPATH				:= ./src/ ./src/init/ ./src/time/ ./src/utils/ \
						./src/monitor/ ./src/free/

SRC					:= main.c time.c utils.c init.c init_utils.c \
						thread_and_mutexes.c routine.c print.c free.c

SRCS				:= $(SRC)

OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

# ----------------------------------- Rules ---------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $@

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