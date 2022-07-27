/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:21:04 by deus              #+#    #+#             */
/*   Updated: 2022/07/27 17:10:52 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

int	load_maps(t_list *input, t_cub *cub)
{
	int	size;
	int	i;

	i = 0;
	input = adjust_input(input);
	size = __lstsize(input);
	cub->size_door_map = size;
	cub->maps = malloc(sizeof(char *) * (size + 1));
	cub->door_map = malloc (sizeof(float *) * (size + 1));
	if (!cub->maps || !cub->door_map)
		return (0);
	cub->maps[size] = NULL;
	while (input)
	{
		cub->maps[i] = (char *)input->content;
		if (__strlen(cub->maps[i]) > 1 && __strrchr(cub->maps[i], '\n'))
			cub->maps[i][__strlen(cub->maps[i]) - 1] = 0;
		cub->door_map[i] = malloc (sizeof(float) * __strlen(cub->maps[i]));
		if (!cub->door_map[i])
			return (__print_error("Malloc error"), 0);
		__memset(cub->door_map[i], 0, __strlen(cub->maps[i]));
		input = input->next;
		i++;
	}
	return (1);
}

static int	check_char_maps(int i, int j, int nb_l, t_cub *cub)
{
	if (!__strchr(" 10NSEW", cub->maps[i][j]))
		return (__print_error("Wrong char"), print_maps_error(cub, i, j), 0);
	if (__strchr("NSEW", cub->maps[i][j]) && !check_player(cub, i, j, nb_l))
		return (print_maps_error(cub, i, j), 0);
	else if ((cub->maps[i][j] == '0')
		&& !check_wall(cub->maps, i, j, nb_l))
		return (print_maps_error(cub, i, j), 0);
	return (1);
}

int	check_maps(t_cub *cub)
{
	int	nb_l;
	int	i;
	int	j;

	i = -1;
	nb_l = maps_size(cub->maps);
	cub->nb_l_maps = nb_l;
	if (nb_l == 0)
		return (__print_error("Empty map"), 0);
	if (nb_l < 0)
		return (__print_error("Info after map end"), 0);
	while (++i < nb_l && cub->maps[i])
	{
		j = -1;
		while (cub->maps[i][++j])
		{
			if (!check_char_maps(i, j, nb_l, cub))
				return (0);
		}
	}
	if (!cub->player.start_orientation)
		return (__print_error("Missing player"), 0);
	return (1);
}
