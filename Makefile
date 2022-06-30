SRC = srcs/main.c
IFLAGS =  -I includes/ -I libft/includes
CFLAGS = -Wall -Wextra -Werror -g3
MLX_DIR = ./minilibx_mms_20200219
MLX_OLDDIR = ./minilibx_opengl
EXTERN_LIB = -L /usr/X11/include/../lib -lXext -lX11
EXTERN_OLDLIB = -framework OpenGL -framework AppKit
CC = cc
OBJS = $(addprefix $(OBJS_PATH), $(SRC:.c=.o))
HEADER = includes/cub3d.h
LIBFT = ./libft
OBJS_PATH = ./objs/
NAME = cub3d
_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m

_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= $'\033[0m

all: $(NAME)

ifeq ($(shell uname -s), Darwin)
MLX_DIR = ${MLX_OLDDIR}
EXTERN_LIB = ${EXTERN_OLDLIB}
endif

$(OBJS_PATH)%.o: %.c $(HEADER)
		mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
		@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"

$(NAME): $(OBJS) ${HEADER} ${LIBFT}
		@printf "%-15s ${_CYAN}${_BOLD}libft${_END}...\n" "Compiling"
		@make -C ${LIBFT} > /dev/null
		@printf "%-15s ${_CYAN}${_BOLD}mlx${_END}...\n" "Compiling"
		@make -C ${MLX_DIR} > /dev/null
		@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
		${CC} ${CFLAGS} ${OBJS} -L ./libft -lft -L ${MLX_DIR} -lmlx ${EXTERN_LIB} -o ${NAME}
		@printf "\n${_GREEN}${_BOLD}[Compilation done !]${_END}\n"

clean :
	rm -rf $(OBJS_PATH)
	make clean -C $(MLX_DIR)
	make clean -C ./libft

fclean : clean
	rm -rf ${NAME}
	rm -rf ./libft/libft.a
	rm -rf $(MLX_DIR)/libmlx.a

re : fclean
	all

.PHONY:  clean fclean re all bonus
