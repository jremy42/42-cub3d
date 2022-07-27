SRC_LIST = main.c\
	create_img.c\
	raycasting.c\
	game.c\
	load_textures.c\
	time.c\
	minimaps.c\
	sprite.c\
	mlx_img_utils.c\
	quit.c\
	draw_sprite.c\
	sprite_utils.c\
	handle_mouse.c\
	init.c\
	raycasting_utils.c\
	colors.c\
	dda.c\
	hook_move.c\
	sight_vector.c\
	hook_door.c\
	hook_key_action.c\
	hook_direction.c\
	hook_direction_2.c\
	gun.c\
	mouse_utils.c

PARSING_BONUS = parsing_bonus/parsing.c\
	parsing_bonus/debug_parsing.c\
	parsing_bonus/loading_maps.c\
	parsing_bonus/check_color.c\
	parsing_bonus/maps_utils.c\
	parsing_bonus/exit.c\
	parsing_bonus/load_info.c\
	parsing_bonus/info_utils.c\

PARSING_MANDATORY = parsing_mandatory/parsing.c\
	parsing_mandatory/debug_parsing.c\
	parsing_mandatory/loading_maps.c\
	parsing_mandatory/check_color.c\
	parsing_mandatory/maps_utils.c\
	parsing_mandatory/exit.c\
	parsing_mandatory/load_info.c\
	parsing_mandatory/info_utils.c

SRC_DIR = ./srcs/

OBJS_DIR = ./objs/

IFLAGS =  -I includes/ -I libft/includes -I mlx_headers/linux
#CFLAGS = -MMD -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS = -MMD -Wall -Wextra -Werror -g3

MLX_DIR = ./minilibx_linux
MLX_MAC = ./minilibx_opengl

EXTERN_LIB = -L /usr/X11/include/../lib -lXext -lX11
EXTERN_MACLIB = -framework OpenGL -framework AppKit
IFLAGS_MAC = -I includes/ -I libft/includes -I mlx_headers/mac

SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRC_LIST:.c=.o))
DEPS = $(patsubst $(OBJS_DIR)%.o, $(OBJS_DIR)%.d, $(OBJS))

HEADER = includes/cub3d.h
LIBFT = ./libft

_GREY=\033[30m
_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_PURPLE=\033[35m
_CYAN=\033[36m
_WHITE=\033[37m
_END=\033[0m

CC = cc

NAME = cub3d

ifeq ($(MAKECMDGOALS), bonus)
	CFLAGS += -D BONUS=1
	SRC_LIST += ${PARSING_BONUS}
else ifeq ($(MAKECMDGOALS), dbonus)
	CFLAGS += -D DEBUG=1
	CFLAGS += -D BONUS=1
	SRC_LIST += ${PARSING_BONUS}
else ifeq ($(MAKECMDGOALS), mdbonus)
	CFLAGS += -D DEBUG=1
	CFLAGS += -D BONUS=1
	CFLAGS += -D MOUSE_HIDE=1
	SRC_LIST += ${PARSING_BONUS}
else ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -D DEBUG=1
	SRC_LIST += ${PARSING_MANDATORY}
else
	SRC_LIST += ${PARSING_MANDATORY}
endif

ifeq ($(shell uname -s), Darwin)
	MLX_DIR = ${MLX_MAC}
	EXTERN_LIB = ${EXTERN_MACLIB}
	IFLAGS = ${IFLAGS_MAC}
endif

MAKEFLAGS += -j

all:  $(NAME)
	@printf "Done\n"
dbonus : $(NAME)
	@printf "Done\n"
mdbonus : $(NAME)
	@printf "Done\n"
bonus : $(NAME)
	@printf "Done\n"
debug: $(NAME)
	@printf "Done\n"

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
		${CC} ${CFLAGS} ${OBJS} -L ./libft -lft -L ${MLX_DIR} -lmlx ${EXTERN_LIB} -lm -o ${NAME}
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

.PHONY:  clean fclean re all bonus dbonus debug
