/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/13 10:51:00 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void	destroy_text_tab(void *mlx, t_img text_img[], int size)
{
	int	i;

	i = 0;
	while(i < size)
	{
		if (mlx && text_img[i].mlx_img)
			mlx_destroy_image(mlx, text_img[i].mlx_img);	
		i++;
	}
}

void	destroy_mlx_data(t_cub *cub)
{
	DEBUG && printf("mlx pointer = [%p], win pointer = [%p]\n", cub->mlx, cub->win);
	if (cub->backgd.mlx_img)
		mlx_destroy_image(cub->mlx, cub->backgd.mlx_img);
	if (cub->screen.mlx_img)
		mlx_destroy_image(cub->mlx, cub->screen.mlx_img);
	if (cub->minimap.mlx_img)
		mlx_destroy_image(cub->mlx, cub->minimap.mlx_img);
	destroy_text_tab(cub->mlx, cub->text_img, 4);
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
	//destroy texture1
	return (0);
}

int __mouse_hook(int button, int x, int y, t_cub *cub)
{
	printf("button pressed : [%d]\n", button);
	printf("Mouse coordinates x/y : (%d:%d)\n", x, y);
	printf("cub player = %p\n", &cub->player);
	printf("cub player.fov = %f\n", cub->player.fov);
	if (button == SCROLL_UP)
	{
		cub->player.fov += 0.05;
	}
	if (button == SCROLL_DOWN)
	{
		cub->player.fov -= 0.05;
	}
	cub->player.plane_x = (- cub->player.dir_y) * cub->player.fov;
	cub->player.plane_y = cub->player.dir_x * cub->player.fov;
	//__key_press(2147483647, cub);
	return (1);
}

int __mouse_move(t_cub *cub)
{
	int x;
	int y;

	mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
		if (x < WIDTH/2)
			rotate(cub, ((-ROTATE_ANGLE) * 2));
		else if ( x > WIDTH/2)
			rotate(cub, ((ROTATE_ANGLE) * 2));
		else
			return (1);
		update_slope(cub);
		//__key_press(2147483647, cub);
		mlx_mouse_move(cub->mlx, cub->win, WIDTH/2, HEIGHT/2);
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
	cub.win = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "My little cube");
	if (!cub.win)
		return (destroy_mlx_data(&cub), __exit_error("Mlx init", &cub), 1);
	if (!create_cub_images(&cub))
		return (destroy_mlx_data(&cub), __exit_error("Create img failed", &cub), 1);
	if (!load_textures(&cub))
		return (destroy_mlx_data(&cub), __exit_error("Create texture failed", &cub), 1);
	mlx_mouse_hook(cub.win, &__mouse_hook, &cub);
	mlx_mouse_move(cub.mlx, cub.win, WIDTH/2, HEIGHT/2);
	mlx_mouse_hide(cub.mlx, cub.win);
	mlx_hook(cub.win, 17, 1L << 1, &__quit, &cub);
	//mlx_hook(cub.win, 6, 0L, &__mouse_move, &cub);
	mlx_hook(cub.win, 2, 1L << 0, &__key_press, &cub);
	mlx_loop_hook(cub.mlx, render_frame, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
