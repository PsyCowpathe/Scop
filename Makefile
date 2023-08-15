CC= clang++
CFLAGS=  -Wall -Wextra -Werror -std=c++17
LDFLAGS=  -lGL -lGLU -lGLEW -lglfw
MAKEFLAGS += --no-print-directory  -j

NAME= scop

HEADER_PATH := ./headers
HEADER := $(wildcard $(HEADER_PATH)/*.hpp)

SRC_PATH := ./src
SRC := $(wildcard $(SRC_PATH)/*.cpp)

OBJS = $(patsubst ./src/%, %, $(patsubst %.cpp, %.o, $(SRC)))
OBJS_DIR = obj
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))


$(OBJS_DIR)/%.o: $(SRC_PATH)/%.cpp Makefile $(HEADER)
		$(CC) $(CFLAGS) -I headers/ -c $< -o $@

all: create_obj_dir $(NAME)

leaks: CFLAGS += -g3 -fsanitize=address
leaks: $(OBJS_PATH)
leaks: $(NAME)
	./$(NAME)

debug: CFLAGS += -g3
debug: $(OBJS_PATH)
debug: $(NAME)
	lldb ./scop

$(NAME): $(OBJS_PATH)
	$(CC) $(CFLAGS) $(OBJS_PATH) $(LDFLAGS) -o $(NAME)

create_obj_dir :
			@rm -f obj 2> /dev/null || true 
			@mkdir -p obj

clean:
	@rm -f $(OBJS_PATH)

fclean: clean
	@rm -f $(NAME)
	@rm -rf obj

re: fclean
	$(MAKE) all

run: all
	./$(NAME)

.PHONY: clean fclean re run debug leaks create_obj_dir
