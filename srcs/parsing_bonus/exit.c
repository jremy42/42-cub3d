/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:53:59 by deus              #+#    #+#             */
/*   Updated: 2022/07/19 18:54:52 by deus             ###   ########.fr       */
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

	i = -1;
	while (++i < 2)
		free(cub->color[i]);
	i = -1;
	while (++i < 4)
		free(cub->text[i]);
	free(cub->maps);
	__lstclear(&cub->input, free);
	DEBUG && printf("Cub data successfully destroyed\n");
}