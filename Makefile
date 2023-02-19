##########   BASE   ##########
# File name
NAME = container

# Sources
#SRCS = ./tests/main_sujet.cpp
#SRCS = ./tests/vector.cpp
#SRCS = ./tests/stack.cpp
SRCS = ./tests/map.cpp
#SRCS = ./tests/set.cpp

# Header/s
HEADER = ./00_vector/vector.hpp
HEADER += ./01_stack/stack.hpp
HEADER += ./02_map/map.hpp
HEADER += ./03_set/set.hpp

OBJS = ${SRCS:.cpp=.o}

# Compilateurs
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98

##########   RULES   ##########
all: $(NAME)

$(NAME): $(OBJS)
	${CC} ${SRCS} -o ${NAME} ${CFLAGS}

%.o: %.cpp $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re