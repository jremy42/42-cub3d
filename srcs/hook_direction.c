/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:53:47 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 09:48:12 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void	__hookleft(t_cub *cub)
{
	__move(cub, -cub->player.plane_x, -cub->player.plane_y);
	(DEBUG == 2) && printf("left\n");
}

void	__hookright(t_cub *cub)
{
	__move(cub, cub->player.plane_x, cub->player.plane_y);
	(DEBUG == 2) && printf("right\n");
}

void	__hookdown(t_cub *cub)
{
	__move(cub, -cub->player.dir_x, -cub->player.dir_y);
	(DEBUG == 2) && printf("down\n");
}

void	__hookup(t_cub *cub)
{
	__move(cub, cub->player.dir_x, cub->player.dir_y);
	(DEBUG == 2) && printf("up\n");
}
