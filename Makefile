MAKEFLAGS += --no-print-directory

NAME = fdf
CC = cc
FLAGS = -Wall -Wextra -Werror -O3
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
	@printf "\r\033[K\033[34mCompiling: $<\033[0m"
	@$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)
	@printf "\r\033[K"

all: $(NAME)

$(LIBFT):
	@echo
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@echo "\n\033[2K\r\033[94mLinking $(NAME) 🗹\033[0m\n"
	@make -C mlx > /dev/null 2>&1
	@echo "\033[2K\r\033[94mLinking mlx 🗹\033[0m\n"
	@$(CC) $(OBJ) $(FRAMEWORK) -o $(NAME) -L $(LIBFT_DIR) -lft
	@len=$$(echo -n "$(NAME)" | wc -c); \
	border=$$(printf '=%.0s' $$(seq 1 $$((len + 36)))); \
	echo "\n\033[94m|$$border|\033[0m"; \
	echo "\033[94m|    🎉 $(NAME) Compilation Complete! 🎉    |\033[0m"; \
	echo "\033[94m|$$border|\033[0m\n"

clean:
	@echo -n "\033[34m"
	@make -C $(LIBFT_DIR) clean
	@make -C mlx/ clean > /dev/null
	@$(RM) $(OBJ)
	@echo "Object files removed\033[0m"

fclean: clean
	@echo -n "\033[34m"
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@make -C mlx/ clean > /dev/null
	@$(RM) $(NAME)
	@echo "Binary files and Libft removed\033[0m"

re: fclean all

norminette:
	@make -C $(LIBFT_DIR) norminette
	@-norminette srcs | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

.PHONY: all clean fclean re bonus norminette