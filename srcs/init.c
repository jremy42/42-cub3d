/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:50:36 by deus              #+#    #+#             */
/*   Updated: 2022/07/25 15:06:45 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "colors.h"

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

int	init_game(t_cub *cub)
{
	DEBUG && print_cub(cub);
	DEBUG && printf("sizeof unsigned int : [%lu]\n", sizeof(unsigned int));
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (__exit_error("Mlx init", cub), 0);
	DEBUG && printf("mlx init ok\n");
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "My little cube");
	if (!cub->win)
		return (__quit(cub), __exit_error("Mlx init", cub), 0);
	DEBUG && printf("mlx win ok\n");
	if (!create_cub_images(cub))
		return (__quit(cub), __exit_error("Create img failed", cub), 0);
	DEBUG && printf("mlx image loading ok\n");
	if (!load_images(cub))
		return (__quit(cub), __exit_error("Create texture failed", cub), 0);
	cub->minimap_height = HEIGHT / 4;
	cub->minimap_width = WIDTH / 4;
	return (1);
}
