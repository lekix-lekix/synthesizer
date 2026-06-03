# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lekix <lekix@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 16:29:27 by kipouliq          #+#    #+#              #
#    Updated: 2026/06/03 15:30:47 by lekix            ###   ########.fr        #
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

OBJS_DIR = .objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $@ $(LIBFLAGS)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re