##########   BASE   ##########
# File name
NAME = container

# Sources
SRCS = ./04_tests/main_sujet.cpp
SRCS = ./04_tests/vector.cpp
SRCS = ./04_tests/stack.cpp
SRCS = ./04_tests/map.cpp
SRCS = ./04_tests/set.cpp

# Header/s
HEADER = ./00_vector/vector.hpp
HEADER += ./01_stack/stack.hpp
HEADER += ./02_map/map.hpp
HEADER += ./03_set/set.hpp
HEADER += ./utils/testeur.hpp
HEADER += ./utils/equal.hpp

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