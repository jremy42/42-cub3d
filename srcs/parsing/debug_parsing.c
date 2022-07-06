/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:46:35 by jremy             #+#    #+#             */
/*   Updated: 2022/07/06 10:09:53 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "colors.h"

void	printer(void *content)
{
	__putstr_fd((char *) content, 2);
}

int	print_cub(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		printf("text[%d] %s\n", i, (char *)cub->text[i]);
	i = -1;
	while (++i < 2)
		printf("color[%d] %s\n", i, (char *)cub->color[i]);
	printf("Color ceiling r:[%d] g:[%d] b:[%d]\n", cub->ceiling.r, cub->ceiling.g, cub->ceiling.b);
	printf("Color floor r:[%d] g:[%d] b:[%d]\n", cub->floor.r, cub->floor.g, cub->floor.b);
	printf("Player start status : [%c] @ (%f:%f)\n", cub->player.start_orientation, cub->player.pos_x, cub->player.pos_y);
	print_maps(cub);
	return (1);
}

int	print_maps(t_cub *cub)
{
	int	i = 0;

	while (cub->maps[i])
		printf("%s\n", cub->maps[i++]);
	return (1);
}

int	print_maps_error(t_cub *cub, int error_i, int error_j)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->maps[i])
	{
		j = 0;
		while (cub->maps[i][j])
		{
			if (j == error_j && i == error_i)
			{
				__putstr_fd(BACK_RED, 2);
				__putchar_fd(cub->maps[i][j], 2);
				__putstr_fd(RESET, 2);
			}
			else
				__putchar_fd(cub->maps[i][j], 2);
			j++;
		}
		__putstr_fd("\n", 2);
		i++;
	}
	__putstr_fd("\n", 2);
	return (1);
}
