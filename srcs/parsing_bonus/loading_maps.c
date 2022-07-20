/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:21:04 by deus              #+#    #+#             */
/*   Updated: 2022/07/20 10:34:37 by jremy            ###   ########.fr       */
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
	cub->maps = malloc(sizeof(char *) * (size + 1));
	cub->maps[size] = NULL;
	cub->door_map = malloc (sizeof(float *) * (size + 1));
	if (!cub->maps || !cub->door_map)
		return (free(cub->maps), free(cub->door_map), 0);
	while (input)
	{
		cub->maps[i] = (char *)input->content;
		if (__strlen(cub->maps[i]) > 1 && __strrchr(cub->maps[i], '\n'))
			cub->maps[i][__strlen(cub->maps[i]) - 1] = 0;
		cub->door_map[i] = malloc (sizeof(float) * __strlen(cub->maps[i]));
		if (!cub->door_map[i])
			return (__putstr_fd("Malloc error\n", 2), 0);
		__memset(cub->door_map[i], 0, __strlen(cub->maps[i]));
		input = input->next;
		i++;
	}
	return (1);
}

int	init_sprite_tab(t_cub *cub)
{
	cub->sprite_tab = malloc(sizeof(t_sprite) * cub->sprite_count);
	if (!cub->sprite_tab)
		return (0);
	__memset(cub->sprite_tab, 0, sizeof(t_sprite) * cub->sprite_count);
	cub->sprite_order = malloc(sizeof(int) * cub->sprite_count);
	if (!cub->sprite_order)
		return (0);
	return (1);
}

int	get_enemy_postion(t_cub *cub, int nb_l)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	if (!init_sprite_tab(cub))
		return (0);
	while (++i < nb_l && cub->maps[i])
	{			
		j = 0;
		while (cub->maps[i][j])
		{
			if (cub->maps[i][j] == 'G')
			{
				cub->sprite_order[k] = k;
				cub->sprite_tab[k].pos_x = j + 0.5f;
				cub->sprite_tab[k].pos_y = i + 0.5f;
				k++;
			}
			j++;
		}
	}
	return (1);
}

int	check_char_maps(int i, int j, int nb_l, t_cub *cub)
{
	if (!__strchr(" GD10NSEW", cub->maps[i][j]))
		return (__putstr_fd("wrong char\n", 2), print_maps_error(cub, i, j), 0);
	if (__strchr("NSEW", cub->maps[i][j]) && !check_player(cub, i, j, nb_l))
		return (print_maps_error(cub, i, j), 0);
	else if ((cub->maps[i][j] == '0'
		|| cub->maps[i][j] == 'G'
		|| cub->maps[i][j] == 'D')
		&& !check_wall(cub->maps, i, j, nb_l))
		return (print_maps_error(cub, i, j), 0);
	if (cub->maps[i][j] == 'D')
		cub->door_map[i][j] = 2;
	if (cub->maps[i][j] == 'G')
				cub->sprite_count++;
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
		return (__putstr_fd("empty map\n", 2), 0);
	if (nb_l < 0)
		return (__putstr_fd("info after map end\n", 2), 0);
	while (++i < nb_l && cub->maps[i])
	{			
		j = 0;
		while (cub->maps[i][j])
		{
			if (!check_char_maps(i, j, nb_l, cub))
				return (0);
			j++;
		}
	}
	if (!get_enemy_postion(cub, nb_l))
		return (__putstr_fd("Malloc error\n", 2), 0);
	if (!cub->player.start_orientation)
		return (__putstr_fd("missing player\n", 2), 0);
	return (1);
}
