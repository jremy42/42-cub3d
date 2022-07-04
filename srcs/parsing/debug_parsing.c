/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:46:35 by jremy             #+#    #+#             */
/*   Updated: 2022/07/04 17:58:31 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printer(void *content)
{
	__putstr_fd((char *) content, 2);
}

int	print_cub(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("text[%d] %s\n", i, (char *)cub->text[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		printf("color[%d] %s\n", i, (char *)cub->color[i]);
		i++;
	}
	printf("Player start status : [%c] @ (%d:%d)\n", cub->player.dir, cub->player.i, cub->player.j);
	printf("color ceiling r:[%d] g:[%d] b:[%d]\n", cub->ceiling.r, cub->ceiling.g, cub->ceiling.b);
	printf("color floor r:[%d] g:[%d] b:[%d]\n", cub->floor.r, cub->floor.g, cub->floor.b);

	print_maps(cub);
	return (1);
}

int	print_maps(t_cub *cub)
{
	int	i = 0;

	while (cub->maps[i])
	{
		printf("%s\n", cub->maps[i]);
		i++;
	}
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
