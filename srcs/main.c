/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/06 10:29:34 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"

void	destroy_mlx_data(t_cub *cub)
{
	DEBUG && printf("mlx pointer = [%p], win pointer = [%p]\n", cub->mlx, cub->win);
	if (cub->backgd.mlx_img)
		mlx_destroy_image(cub->mlx, cub->backgd.mlx_img);
	if (cub->screen.mlx_img)
		mlx_destroy_image(cub->mlx, cub->screen.mlx_img);
	if (cub->minimap.mlx_img)
		mlx_destroy_image(cub->mlx, cub->minimap.mlx_img);	
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	#ifdef __linux__
	if (cub->mlx)
	{
		DEBUG && printf("LINUX : Destroying display\n");
		mlx_destroy_display(cub->mlx);
	}
	#endif
	free(cub->mlx);
	DEBUG && printf("Mlx data successfully destroyed\n");
	exit(0);
}


int	__quit(t_cub *cub)
{
	destroy_cub_data(cub);
	destroy_mlx_data(cub);
	return (0);
}

int	__key_press(int keycode, t_cub *cub)
{
	DEBUG && printf("Key pressed [%d]\n", keycode);
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}

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
	DEBUG && print_cub(&cub);
	__putstr_fd("Hello Raycasted World\n", 1);
	cub.mlx = mlx_init();
	if (!cub.mlx)
		return (__exit_error("Mlx init", &cub), 1);
	cub.win = mlx_new_window(cub.mlx, 640, 480, "My little cube");
	if (!cub.win)
		return (destroy_mlx_data(&cub), __exit_error("Mlx init", &cub), 1);
	if (!create_cub_images(&cub))
		return (destroy_mlx_data(&cub), __exit_error("Create img failed", &cub), 1);
	mlx_hook(cub.win, 17, 1L << 1, &__quit, &cub);
	mlx_hook(cub.win, 2, 1L << 0, &__key_press, &cub);
	mlx_loop_hook(cub.mlx, game, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
