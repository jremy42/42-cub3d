/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/21 12:36:08 by jremy            ###   ########.fr       */
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
	while (i < size)
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
	destroy_text_tab(cub->mlx, cub->text_img[0], 4);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_do_key_autorepeaton(cub->mlx);
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

int	__mouse_hook(int button, int x, int y, t_cub *cub)
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
	if (button == 1)
		cub->gun_animate = 1;
	cub->player.plane_x = (- cub->player.dir_y) * cub->player.fov;
	cub->player.plane_y = cub->player.dir_x * cub->player.fov;
	//__key_press(2147483647, cub);
	return (1);
}

int __mouse_move(t_cub *cub)
{
	int	x;
	int	y;

	x = WIDTH / 2;
	y = 0;
	y++;
	#ifdef __linux__
	mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
	#endif
	#ifdef __MACH__
	mlx_mouse_get_pos(cub->win, &x, &y);
	#endif
	if (x != WIDTH/2)
		rotate(cub, ((ROTATE_ANGLE) * 0.02 * (x - WIDTH/2)));
	else
		return (1);
	update_slope(cub);
	#ifdef __linux__
	mlx_mouse_move(cub->mlx, cub->win, WIDTH/2, HEIGHT/2);
	#endif
	#ifdef __MACH__
	mlx_mouse_move(cub->win, WIDTH/2, HEIGHT/2);
	#endif
	return (1);
}

void	set_ressources_file_names(t_cub *cub)
{
	cub->gun_img_file[0] = PISTOL_0;
	cub->gun_img_file[1] = PISTOL_1;
	cub->gun_img_file[2] = PISTOL_2;
	cub->gun_img_file[3] = PISTOL_3;
	cub->gun_img_file[4] = PISTOL_4;
	cub->guard_img_file[0] = GUARD_W;
	cub->guard_img_file[1] = GUARD_F1;
	cub->guard_img_file[2] = GUARD_F2;
	cub->guard_img_file[3] = GUARD_F3;
	cub->guard_img_file[4] = GUARD_D1;
	cub->guard_img_file[5] = GUARD_D2;
	cub->guard_img_file[6] = GUARD_D3;
	cub->guard_img_file[7] = GUARD_D4;
	cub->guard_img_file[8] = GUARD_D5;
}

void	set_hook_fx(t_cub *cub)
{
	cub->hook_fx[UP] = __hookup;
	cub->hook_fx[DOWN] = __hookdown;
	cub->hook_fx[LEFT] = __hookleft;
	cub->hook_fx[RIGHT] = __hookright;
	cub->hook_fx[OPEN_DOOR] = __switch_door;
}

int	main(int ac, char **av)
{
	t_cub	cub;

	__memset(&cub, 0, sizeof(cub));
	set_hook_fx(&cub);
	set_ressources_file_names(&cub);

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
	DEBUG && printf("sizeof unsigned int : [%lu]\n", sizeof(unsigned int));
	cub.mlx = mlx_init();
	if (!cub.mlx)
		return (__exit_error("Mlx init", &cub), 1);
	DEBUG && printf("mlx init ok\n");
	cub.win = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "My little cube");
	if (!cub.win)
		return (destroy_mlx_data(&cub), __exit_error("Mlx init", &cub), 1);
	DEBUG && printf("mlx win ok\n");
	if (!create_cub_images(&cub))
		return (destroy_mlx_data(&cub), __exit_error("Create img failed", &cub), 1);
	DEBUG && printf("mlx image loading ok\n");
	if (!load_images(&cub))
		return (destroy_mlx_data(&cub), __exit_error("Create texture failed", &cub), 1);
	cub.minimap_height = HEIGHT/4;
	cub.minimap_width = WIDTH/4;
	DEBUG && printf("mlx textures loading ok\n");
	mlx_mouse_hook(cub.win, &__mouse_hook, &cub);
	DEBUG && printf("mlx hooking mouse ok\n");
	mlx_mouse_hide(cub.mlx, cub.win);
	DEBUG && printf("mlx mouse hiding ok\n");
	mlx_hook(cub.win, 17, 1L << 1, &__quit, &cub);
	DEBUG && printf("mlx hook quit ok\n");
	mlx_hook(cub.win, 2, 1L << 0, &__key_press, &cub);
	DEBUG && printf("mlx key press ok\n");
	mlx_hook(cub.win, 3, 1L << 0, &__key_release, &cub);
	DEBUG && printf("mlx key release ok\n");
	mlx_do_key_autorepeatoff(cub.mlx);
	DEBUG && printf("mlx autorepeat off ok\n");
	mlx_loop_hook(cub.mlx, render_frame, &cub);
	DEBUG && printf("mlx rendering loop hook ok\n");
	#ifdef __linux__
	mlx_mouse_move(cub.mlx, cub.win, WIDTH/2, HEIGHT/2);
	#endif
	#ifdef __MACH__
	mlx_mouse_move(cub.win, WIDTH/2, HEIGHT/2);
	#endif
	rotate(&cub, 0.01f);
	mlx_loop(cub.mlx);
	DEBUG && printf("mlx looping done (this should not occur)\n");
	return (0);
}
