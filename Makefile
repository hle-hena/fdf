MAKEFLAGS += --no-print-directory

NAME = fdf
CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g
RM = rm -f

FRAMEDIR = ./mlx
FRAMEWORK = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz -lXfixes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FDF =	color_utils.c		color.c			draw_utils.c		\
		draw.c				end.c			event.c				\
		float.c				fps.c			init.c				\
		main.c				mlx_hook.c		mlx_utils.c			\
		movement.c			parser_utils.c	parser.c			\
		projection_utils.c	projection.c	rotate_euler.c		\
		rotate_quaternion.c	rotate.c		status.c			\
		vec.c				draw_persp.c

FDF_SRC = $(addprefix srcs/, $(FDF))

OBJ = $(FDF_SRC:.c=.o)

.c.o: 
	@$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@make -C mlx
	@$(CC) $(OBJ) $(FRAMEWORK) -o $(NAME) -L $(LIBFT_DIR) -lft
	@echo "$(NAME) compiled successfully!"

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C mlx/ clean
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "Object files removed"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@make -C mlx/ clean
	@$(RM) $(NAME) checker
	@echo "Binary files and Libft removed"

re: fclean all

norminette:
	@make -C $(LIBFT_DIR) norminette
	@-norminette srcs | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

.PHONY: all clean fclean re bonus norminette