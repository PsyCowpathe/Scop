CC= clang++
CFLAGS=  -std=c++17 -O2
LDFLAGS= -lglfw -ldl -lpthread -lX11 -lXrandr -lXi -lGL -lGLEW -g3 -fsanitize=address 
# -fsanitize=address -stdlib=libc++ -D_LIBCPP_DEBUG -g
# Warning : g3 and fsanitize can cause a stack-overflow !

NAME= scop

HEADER= \
		inc/shader.hpp

SRC= \
	srcs/main.cpp \
	shader/shader.cpp


OBJS = $(SRC:%.cpp=%.o)


%.o:	%.cpp Makefile $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
rel: $(NAME)

debug: CFLAGS+= -DDEBUG -g
debug: $(NAME)


$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

run: $(NAME)
	./$(NAME)

.PHONY: clean fclean re run debug