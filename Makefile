SRC_LIST = main.c\
	parsing/parsing.c\
	parsing/debug_parsing.c\
	parsing/loading_maps.c\
	parsing/check_color.c\
	create_img.c\
	game.c\
	hook.c

SRC_DIR = ./srcs/

OBJS_DIR = ./objs/

IFLAGS =  -I includes/ -I libft/includes
CFLAGS = -MMD -Wall -Wextra -Werror -g3

MLX_DIR = ./minilibx_linux
MLX_MAC = ./minilibx_opengl

EXTERN_LIB = -L /usr/X11/include/../lib -lXext -lX11
EXTERN_MACLIB = -framework OpenGL -framework AppKit

SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRC_LIST:.c=.o))
DEPS = $(patsubst $(OBJS_DIR)%.o, $(OBJS_DIR)%.d, $(OBJS))

HEADER = includes/cub3d.h
LIBFT = ./libft

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= $'\033[0m

CC = cc

NAME = cub3d

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -D DEBUG=1
endif

ifeq ($(shell uname -s), Darwin)
MLX_DIR = ${MLX_MAC}
EXTERN_LIB = ${EXTERN_MACLIB}
endif

all: 
	make -j -s $(NAME)
	@printf "Done\n"
	
debug: fclean $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
		printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"

$(NAME): $(OBJS) ${HEADER} ${LIBFT}
		printf "%-15s ${_CYAN}${_BOLD}libft${_END}...\n" "Compiling"
		make -C ${LIBFT} > /dev/null
		printf "%-15s ${_CYAN}${_BOLD}mlx${_END}...\n" "Compiling"
		make -C ${MLX_DIR} > /dev/null 2>&1
		printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
		${CC} ${CFLAGS} ${OBJS} -L ./libft -lft -L ${MLX_DIR} -lmlx ${EXTERN_LIB} -o ${NAME}
		printf "\n${_GREEN}${_BOLD}[Compilation done !]${_END}\n"

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(MLX_DIR)
	make clean -C ./libft

fclean : clean
	rm -rf ${NAME}
	rm -rf ./libft/libft.a
	rm -rf $(MLX_DIR)/libmlx.a

re : fclean
	make

-include $(DEPS)

.PHONY:  clean fclean re all bonus
