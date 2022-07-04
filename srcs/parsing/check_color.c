#include "cub3d.h"

int	count_char_in_str(char *str, char to_find)
{
	int	count;

	count = 0;
	while (*str)
		count += (*str++ == to_find);
	return (count);
}

int	load_color(char *color_str, t_color *color_struct)
{
	char	**split_color;

	if (__strlen(color_str) < 5)
		return (0);
	if (!__isdigit(color_str[0])
		|| !__isdigit(color_str[__strlen(color_str) - 1]))
		return (__putendl_fd("Wrong color format", 2), 0);
	if (count_char_in_str(color_str, ',') != 2)
		return (__putendl_fd("Too many/few separator in color", 2), 0);
	split_color = __split(color_str, ',');
	if (!split_color)
		return (__putendl_fd("Malloc error", 2), 0);
	if (size_split(split_color) != 3)
		return (free_split(split_color),
			__putendl_fd("Wrong color component amount", 2), 0);
	if (!__atobyte(split_color[0], &color_struct->r)
		|| !__atobyte(split_color[1], &color_struct->g)
		|| !__atobyte(split_color[2], &color_struct->b))
		return (free_split(split_color),
			__putendl_fd("Wrong color component", 2), 0);
	return (free_split(split_color), 1);
}

int	check_color(t_cub *cub)
{
	if (!load_color(cub->color[0], &cub->ceiling))
		return (0);
	if (!load_color(cub->color[1], &cub->floor))
		return (0);
	return (1);
}
