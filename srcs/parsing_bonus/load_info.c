/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:41:12 by deus              #+#    #+#             */
/*   Updated: 2022/07/19 20:43:05 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	missing_info_cub(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!cub->text[i])
			return (1);
		i++;
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

int	get_pos(char **ret)
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

int	load_info(char **ret, t_cub *cub)
{
	int	pos;

	pos = get_pos(ret);
	if (!pos)
		return (__putstr_fd("No such a info\n", 2), 0);
	if (pos == 7)
		cub->door = ret[1];
	else if (pos > 0 && pos < 5)
	{
		if (cub->text[pos - 1])
			return (__putstr_fd("Too many info\n", 2), 0);
		cub->text[pos - 1] = ret[1];
	}
	else if (pos >= 5 && pos < 7)
	{
		if (cub->color[pos - 5])
			return (__putstr_fd("Too many info\n", 2), 0);
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

void	get_info(t_list *input, t_cub *cub)
{
	char	**ret;
	char	*curent_string;

	while (input && missing_info_cub(cub))
	{
		curent_string = (char *)input->content;
		ret = __split_charset(curent_string, " \f\t\n\r\v");
		if (__strlen(curent_string) && !ret)
			__exit_error("malloc error", cub);
		if (size_split(ret) == 0)
		{
			free_split(ret);
			input = input->next;
			continue ;
		}
		if (size_split(ret) != 2)
			return (printf("[%s]\n", ret[0]), free_split(ret),
				__exit_error("wrong info format", cub));
		if (!load_info(ret, cub))
			return (free_split(ret), __exit_error("parsing error", cub));
		input = input->next;
	}
	if (!load_maps(input, cub))
		return (__exit_error("malloc error", cub));
}
