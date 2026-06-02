# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lekix <lekix@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 16:29:27 by kipouliq          #+#    #+#              #
#    Updated: 2026/06/02 17:14:46 by lekix            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

CXX = c++ -D__LINUX_ALSA__ 

FLAGS = -Wall -Wextra -Werror -g3 -O3

LIBFLAGS = -lpthread -lasound

SRCS = rtaudio/RtAudio.cpp \
		src/Synth.cpp \
		src/Osc.cpp \
		src/main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SCRS)%.cpp
	$(CXX) $(FLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
# 	cd rtaudio && ./autogen.sh && make
	$(CXX) $(FLAGS) $(OBJS) -o $@ $(LIBFLAGS)

clean:
	rm -rf ./src/*.o

fclean:	clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re