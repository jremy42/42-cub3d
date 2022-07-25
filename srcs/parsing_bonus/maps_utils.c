/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:16:24 by deus              #+#    #+#             */
/*   Updated: 2022/07/25 14:55:44 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

int	check_wall(char **maps, int i, int j, int nb_l)
{
	if (j == 0 || j == ((int)__strlen(maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__print_error("0 or G or D on border"), 0);
	if (j >= ((int)__strlen(maps[i + 1]) - 1)
		|| j >= ((int)__strlen(maps[i - 1]) - 1))
		return (__print_error("Surrouding wall missing"), 0);
	if (maps[i + 1][j] == ' '
		|| maps[i + 1][j + 1] == ' '
		|| maps[i][j + 1] == ' '
		|| maps[i - 1][j + 1] == ' '
		|| maps[i - 1][j] == ' '
		|| maps[i - 1][j - 1] == ' '
		|| maps[i][j - 1] == ' '
		|| maps[i + 1][j - 1] == ' ')
		return (__print_error("Space near 0"), 0);
	return (1);
}

int	check_player(t_cub *cub, int i, int j, int nb_l)
{
	if (cub->player.start_orientation)
		return (__print_error("To many player"), 0);
	if (j == 0 || j == ((int)__strlen(cub->maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__print_error("Player on border"), 0);
	if (j >= ((int)__strlen(cub->maps[i + 1]) - 1)
		|| j >= ((int)__strlen(cub->maps[i - 1]) - 1))
		return (__print_error("Surrouding wall missing near player"), 0);
	if (cub->maps[i + 1][j] == ' '
		|| cub->maps[i + 1][j + 1] == ' '
		|| cub->maps[i][j + 1] == ' '
		|| cub->maps[i - 1][j + 1] == ' '
		|| cub->maps[i - 1][j] == ' '
		|| cub->maps[i - 1][j - 1] == ' '
		|| cub->maps[i][j - 1] == ' '
		|| cub->maps[i + 1][j - 1] == ' ')
		return (__print_error("space near player"), 0);
	cub->player.start_orientation = cub->maps[i][j];
	cub->player.pos_x = j + 0.5;
	cub->player.pos_y = i + 0.5;
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
		if (input->content && __strcmp((char *)input->content, "\n"))
			break ;
		input = input->next;
	}
	return (input);
}
