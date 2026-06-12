# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lekix <lekix@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 16:29:27 by kipouliq          #+#    #+#              #
#    Updated: 2026/06/02 15:31:12 by lekix            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = a.out
NAME_LIB = lbuffer.a
SANITIZE = a.out_san
CXX      = c++
FLAGS    = -Wall -Wextra -Werror -g3 -O3
SAN_FLAG = -fsanitize=thread
SRCS     = main.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $@ 

$(SANITIZE): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $@ $(SAN_FLAG)

$(NAME_LIB): $(OBJS)
	ar -rcs $@ $(OBJ)

san: $(SANITIZE)

lib: $(NAME_LIB)

clean:
	rm -rf ./*.o

fclean: clean
	rm -f $(NAME) $(SANITIZE)

re: fclean
	make all

.PHONY: all san clean fclean re