/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/22 17:57:07 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

#ifdef __linux__

void	__game_loop(t_cub *cub)
{
	DEBUG && printf("mlx textures loading ok\n");
	mlx_mouse_hook(cub->win, &__mouse_hook, cub);
	DEBUG && printf("mlx hooking mouse ok\n");
	MOUSE_HIDE && mlx_mouse_hide(cub->mlx, cub->win);
	DEBUG && printf("mlx mouse hiding ok\n");
	mlx_hook(cub->win, 17, 1L << 1, &__quit, cub);
	DEBUG && printf("mlx hook quit ok\n");
	mlx_hook(cub->win, 2, 1L << 0, &__key_press, cub);
	DEBUG && printf("mlx key press ok\n");
	mlx_hook(cub->win, 3, 1L << 0, &__key_release, cub);
	DEBUG && printf("mlx key release ok\n");
	mlx_do_key_autorepeatoff(cub->mlx);
	DEBUG && printf("mlx autorepeat off ok\n");
	mlx_loop_hook(cub->mlx, render_frame, cub);
	DEBUG && printf("mlx rendering loop hook ok\n");
	mlx_mouse_move(cub.mlx, cub.win, WIDTH / 2, HEIGHT / 2);
	rotate(cub, 0.01f);
	mlx_loop(cub->mlx);
	DEBUG && printf("mlx looping done (this should not occur)\n");
}
#endif

#ifdef __MACH__

void	__game_loop(t_cub *cub)
{
	DEBUG && printf("mlx textures loading ok\n");
	mlx_mouse_hook(cub->win, &__mouse_hook, cub);
	DEBUG && printf("mlx hooking mouse ok\n");
	MOUSE_HIDE && mlx_mouse_hide(cub->mlx, cub->win);
	DEBUG && printf("mlx mouse hiding ok\n");
	mlx_hook(cub->win, 17, 1L << 1, &__quit, cub);
	DEBUG && printf("mlx hook quit ok\n");
	mlx_hook(cub->win, 2, 1L << 0, &__key_press, cub);
	DEBUG && printf("mlx key press ok\n");
	mlx_hook(cub->win, 3, 1L << 0, &__key_release, cub);
	DEBUG && printf("mlx key release ok\n");
	mlx_do_key_autorepeatoff(cub->mlx);
	DEBUG && printf("mlx autorepeat off ok\n");
	mlx_loop_hook(cub->mlx, render_frame, cub);
	DEBUG && printf("mlx rendering loop hook ok\n");
	mlx_mouse_move(cub->win, WIDTH / 2, HEIGHT / 2);
	rotate(cub, 0.01f);
	mlx_loop(cub->mlx);
	DEBUG && printf("mlx looping done (this should not occur)\n");
}
#endif

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
	if (!init_game(&cub))
		return (1);
	__game_loop(&cub);
	return (0);
}
