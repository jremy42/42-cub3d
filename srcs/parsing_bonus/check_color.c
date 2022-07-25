/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:52:56 by deus              #+#    #+#             */
/*   Updated: 2022/07/25 15:01:10 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

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
		return (__print_error("Wrong color format"), 0);
	if (count_char_in_str(color_str, ',') != 2)
		return (__print_error("Too many/few separator in color"), 0);
	split_color = __split(color_str, ',');
	if (!split_color)
		return (__print_error("Malloc error"), 0);
	if (size_split(split_color) != 3)
		return (free_split(split_color),
			__print_error("Wrong color component amount"), 0);
	if (!__atobyte(split_color[0], &color_struct->r)
		|| !__atobyte(split_color[1], &color_struct->g)
		|| !__atobyte(split_color[2], &color_struct->b))
		return (free_split(split_color),
			__print_error("Wrong color component"), 0);
	return (free_split(split_color), 1);
}

int	create_color(t_color color)
{
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

int	check_color(t_cub *cub)
{
	if (!load_color(cub->color[0], &cub->ceiling))
		return (0);
	if (!load_color(cub->color[1], &cub->floor))
		return (0);
	cub->ceiling.trgb = create_color(cub->ceiling);
	cub->floor.trgb = create_color(cub->floor);
	return (1);
}
