/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_direction_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:47 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 09:50:53 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void	__hook_rotate_left(t_cub *cub)
{
	rotate(cub, ROTATE_ANGLE * (-1.0f));
	update_slope(cub);
	(DEBUG == 2) && printf("rotate left\n");
}

void	__hook_rotate_right(t_cub *cub)
{
	rotate(cub, ROTATE_ANGLE * (1.0f));
	update_slope(cub);
	(DEBUG == 2) && printf("rotate right\n");
}
