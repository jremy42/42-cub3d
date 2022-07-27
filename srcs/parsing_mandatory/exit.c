/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:53:59 by deus              #+#    #+#             */
/*   Updated: 2022/07/27 09:14:54 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

void	__print_error(char *error)
{
	__putendl_fd("Error", 2);
	__putendl_fd(error, 2);
}

void	__exit_error(char *error, t_cub *cub)
{
	if (error)
	{
		__putendl_fd("Error", 2);
		__putendl_fd(error, 2);
	}
	destroy_cub_data(cub);
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

	i = -1;
	while (++i < 2)
		free(cub->color[i]);
	i = -1;
	while (++i < 4)
	{
		free(cub->text[i][0]);
		cub->text[i][0] = NULL;
	}
	i = -1;
	while (++i < cub->size_door_map)
		free(cub->door_map[i]);
	free(cub->maps);
	free(cub->door_map);
	if (cub->sprite_tab)
		free(cub->sprite_tab);
	if (cub->input)
		__lstclear(&cub->input, free);
}