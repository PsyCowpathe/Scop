CC= clang++
CFLAGS=  -Wall -Wextra -Werror -std=c++17 -O2
LDFLAGS=  -lGL -lGLEW -lglfw \
-ldl  -lX11 -lXrandr -lXi \
-g3 -fsanitize=address # this can cause a stack overflow !
MAKEFLAGS += --no-print-directory -j

NAME= scop

HEADER_PATH := ./headers
HEADER := $(wildcard $(HEADER_PATH)/*.hpp)

SRC_PATH := ./src
SRC := $(wildcard $(SRC_PATH)/*.cpp)
OBJS = $(SRC:%.cpp=%.o)


%.o:	%.cpp Makefile $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
rel: $(NAME)

debug: CFLAGS += -DDEBUG -g3
debug: $(OBJS)
debug: $(NAME)
	lldb ./scop

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
