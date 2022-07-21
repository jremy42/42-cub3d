/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:53:59 by deus              #+#    #+#             */
/*   Updated: 2022/07/21 15:54:16 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

void	__exit_error(char *error, t_cub *cub)
{
	destroy_cub_data(cub);
	__putendl_fd("Error", 2);
	__putendl_fd(error, 2);
	exit(1);
}

void	__exit_error_get_input(char *error, t_list *lst, int fd)
{
	__lstclear(&lst, free);
	if (fd >= 0)
		close(fd);
	__putendl_fd("Error", 2);
	__putendl_fd(error, 2);
	exit(1);
}

void	destroy_cub_data(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 2)
		free(cub->color[i]);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 6)
			free(cub->text[i][j]);
	}
	i = -1;
	while (++i < cub->size_door_map)
		free(cub->door_map[i]);
	free(cub->door_map);
	free(cub->maps);
	if (cub->input)
		__lstclear(&cub->input, free);
	DEBUG && printf("Cub data successfully destroyed\n");
}
