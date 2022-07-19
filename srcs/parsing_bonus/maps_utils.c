/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:16:24 by deus              #+#    #+#             */
/*   Updated: 2022/07/19 18:55:44 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

int	check_wall(char **maps, int i, int j, int nb_l)
{
	if (j == 0 || j == ((int)__strlen(maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__putstr_fd("0 on border\n", 2), 0);
	if (j >= ((int)__strlen(maps[i + 1]) - 1)
		|| j >= ((int)__strlen(maps[i - 1]) - 1))
		return (__putstr_fd("surrouding wall missing\n", 2), 0);
	if (maps[i + 1][j] == ' '
		|| maps[i + 1][j + 1] == ' '
		|| maps[i][j + 1] == ' '
		|| maps[i - 1][j + 1] == ' '
		|| maps[i - 1][j] == ' '
		|| maps[i - 1][j - 1] == ' '
		|| maps[i][j - 1] == ' '
		|| maps[i + 1][j - 1] == ' ')
		return (__putstr_fd("space near 0\n", 2), 0);
	return (1);
}

int	check_player(t_cub *cub, int i, int j, int nb_l)
{
	if (cub->player.start_orientation)
		return (__putstr_fd("to many player\n", 2), 0);
	if (j == 0 || j == ((int)__strlen(cub->maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__putstr_fd("player on border\n", 2), 0);
	if (j >= ((int)__strlen(cub->maps[i + 1]) - 1)
		|| j >= ((int)__strlen(cub->maps[i - 1]) - 1))
		return (__putstr_fd("surrouding wall missing near player\n", 2), 0);
	if (cub->maps[i + 1][j] == ' '
		|| cub->maps[i + 1][j + 1] == ' '
		|| cub->maps[i][j + 1] == ' '
		|| cub->maps[i - 1][j + 1] == ' '
		|| cub->maps[i - 1][j] == ' '
		|| cub->maps[i - 1][j - 1] == ' '
		|| cub->maps[i][j - 1] == ' '
		|| cub->maps[i + 1][j - 1] == ' ')
		return (__putstr_fd("space near player\n", 2), 0);
	cub->player.start_orientation = cub->maps[i][j];
	cub->player.pos_x = j;
	cub->player.pos_y = i;
	cub->maps[i][j] = '0';
	return (1);
}

int	maps_size(char **maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps[i])
	{
		if (!__strcmp(maps[i], "\n"))
			break ;
		i++;
	}
	j = i;
	while (maps[j])
	{
		if (__strcmp(maps[j], "\n"))
			return (-1);
		j++;
	}
	return (i);
}

t_list	*adjust_input(t_list *input)
{
	while (input)
	{
		if (!__strcmp((char *)input->content, "\n"))
		{
			input = input->next;
			break ;
		}
		input = input->next;
	}
	return (input);
}
