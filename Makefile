CC= clang++
CFLAGS=  -std=c++17 -O2
LDFLAGS=  -lGL -lGLU -lGLEW -lglfw
MAKEFLAGS += --no-print-directory -j

NAME= scop

HEADER= \
	render.hpp \
	loadShadersTmp.hpp

SRC= \
	main.cpp \
	render.cpp \
	loadShadersTmp.cpp

OBJS = $(SRC:%.cpp=%.o)


%.o: %.cpp Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
rel: $(NAME)

debug: CFLAGS+= -DDEBUG -g
debug: $(NAME)

leaks: CFLAGS += -g3 -fsanitize=address
leaks: $(OBJS)
leaks: $(NAME) 
	./$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

run: $(NAME)
	./$(NAME)


.PHONY: clean fclean re run debug leaks