/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:41:12 by deus              #+#    #+#             */
/*   Updated: 2022/07/25 18:52:27 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	get_pos(char **ret)
{
	int	pos;

	pos = !__strcmp(ret[0], "NO") * 1
		+ !__strcmp(ret[0], "SO") * 2
		+ !__strcmp(ret[0], "EA") * 3
		+ !__strcmp(ret[0], "WE") * 4
		+ !__strcmp(ret[0], "C") * 5
		+ !__strcmp(ret[0], "F") * 6
		+ !__strcmp(ret[0], "D") * 7;
	return (pos);
}

static int	load_texture_path(void *text[6], char **ret)
{
	int	i;

	i = 1;
	while (ret[i])
	{
		text[i - 1] = ret[i];
		i++;
	}
	return (1);
}

int	missing_info_cub(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 6)
			if (!cub->text[i][j])
				return (1);
	}
	i = 0;
	while (i < 2)
	{
		if (!cub->color[i])
			return (1);
		i++;
	}
	if (!cub->door)
		return (1);
	return (0);
}

int	load_info(char **ret, t_cub *cub)
{
	int	pos;

	pos = get_pos(ret);
	if (!pos)
		return (__putstr_fd("No such a info\n", 2), 0);
	else if (pos > 0 && pos < 5)
	{
		if (cub->text[pos - 1][0])
			return (__putstr_fd("Too many info\n", 2), 0);
		load_texture_path(cub->text[pos - 1], ret);
	}
	else if (pos >= 5 && pos <= 7)
	{
		if (cub->color[pos - 5] || size_split(ret) != 2)
			return (__putstr_fd("Too many info for ceiling, floor or door\n",
					2), 0);
		if (pos == 7)
			cub->door = ret[1];
		else
			cub->color[pos - 5] = ret[1];
	}
	free(ret[0]);
	ret[0] = NULL;
	return (free(ret), 1);
}

void	load_player_info(t_cub *cub)
{
	if (cub->player.start_orientation == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
	}
	if (cub->player.start_orientation == 'E')
	{
		cub->player.dir_x = 1;
		cub->player.dir_y = 0;
	}
	if (cub->player.start_orientation == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
	}
	if (cub->player.start_orientation == 'S')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = 1;
	}
	cub->player.fov = FOV;
	cub->player.plane_x = (-cub->player.dir_y) * FOV;
	cub->player.plane_y = cub->player.dir_x * FOV;
}
