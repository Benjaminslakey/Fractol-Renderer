NAME= fractol

FLAGS= -Wall -Wextra -Werror -Ofast

SRCS= fractol \
	  fractal_math \
	  events \
	  draw \
	  program \
	  utility \
	  view \


CC= gcc

FILES= $(addprefix srcs/, $(SRCS))

CFILES= $(addsuffix .c, $(FILES))

OFILES=	$(addsuffix .o, $(FILES))

LIBFT= libft.a

MLX_LIB= libmlx.a

LDFLAGS= -L./ -lmx

HEADER= -Iincludes

FRAMEWORK= -framework OpenGL -framework AppKit

.PHONY: make all clean fclean re

all: $(NAME)

$(NAME): $(CFILES) $(LIBFT) $(MLX_LIB)
	$(CC) $(FLAGS) $(HEADER) -o $(NAME) $(CFILES) $(LDFLAGS) $(FRAMEWORK) $(MLX_LIB) $(LIBFT) 

$(LIBFT):
	make -C libft
	mv libft/$(LIBFT) .

$(MLX_LIB):
	make -C mlx
	mv mlx/$(MLX_LIB) .

clean:
	make clean -C libft
	make clean -C mlx
	rm -f $(LIBFT) $(MLX_LIB)

fclean: clean
	rm -f $(NAME)

re: fclean all
