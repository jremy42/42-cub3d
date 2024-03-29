/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/26 17:40:54 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void	update_slope(t_cub *cub)
{
	cub->player.slope_dir = cub->player.dir_y / cub->player.dir_x;
	cub->player.delta_dist_x = sqrt(1 + pow(cub->player.slope_dir, 2));
	cub->player.delta_dist_y = sqrt(1 + pow(1 / cub->player.slope_dir, 2));
}

void	rotate(t_cub *cub, float angle)
{
	float	old_dir_x;
	float	old_dir_y;
	float	old_plane_x;
	float	old_plane_y;

	old_dir_x = cub->player.dir_x;
	old_dir_y = cub->player.dir_y;
	old_plane_x = cub->player.plane_x;
	old_plane_y = cub->player.plane_y;
	cub->player.dir_x = old_dir_x * cos(angle)
		- old_dir_y * sin(angle);
	cub->player.dir_y = old_dir_x * sin(angle)
		+ old_dir_y * cos(angle);
	cub->player.plane_x = old_plane_x * cos(angle)
		- old_plane_y * sin(angle);
	cub->player.plane_y = old_plane_x * sin(angle)
		+ old_plane_y * cos(angle);
	cub->player.plane_norm = sqrt(pow(cub->player.plane_x, 2)
			+ pow(cub->player.plane_y, 2));
}

int	__mouse_hook(int button, int x, int y, t_cub *cub)
{
	DEBUG && printf("button pressed : [%d]\n", button);
	DEBUG && printf("Mouse coordinates x/y : (%d:%d)\n", x, y);
	DEBUG && printf("cub player = %p\n", &cub->player);
	DEBUG && printf("cub player.fov = %f\n", cub->player.fov);
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
	if (FOV_MODIFIABLE)
	{
		cub->player.plane_x = (-cub->player.dir_y) * cub->player.fov;
		cub->player.plane_y = cub->player.dir_x * cub->player.fov;
	}
	return (1);
}

int	__mouse_move(t_cub *cub)
{
	int	x;
	int	y;

	wrapper_mouse_get_pos(cub, &x, &y);
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		cub->action = 0;
	if (BONUS && x != WIDTH / 2)
	{
		rotate(cub, ((ROTATE_ANGLE) * 0.02 * (x - WIDTH / 2)));
		update_slope(cub);
	}
	else
		return (1);
	center_mouse(cub);
	return (1);
}
