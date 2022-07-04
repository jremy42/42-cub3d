/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/04 15:29:30 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	__memset(&cub, 0, sizeof(cub));
	if (ac != 2)
	{
		__putstr_fd("Error\nneed maps\n", 2);
		exit(1);
	}
	if (__strlen(av[1]) < 5
		|| !__strstr(av[1], ".cub")
		|| __strcmp(av[1] + __strlen(av[1]) - 4, ".cub"))
		return (__putstr_fd("Error\nWrong map name extension\n", 2), 1);
	parsing(av, &cub);
	print_cub(&cub);
	__putstr_fd("Hello Raycasted World\n", 1);
	destroy_cub_data(&cub);
	return (0);
}
