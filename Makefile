NAME = so_long

CC = cc

SRC = main.c

OBJ := $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJ) mlx/libmlx.a
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

mlx/libmlx.a:
	make -C mlx/

clean:
	rm -rf $(OBJ)

fclean: clean
	make clean -C mlx/
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re