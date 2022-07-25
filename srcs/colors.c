/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:45:19 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 12:45:40 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"
#include "colors.h"

int	dim_color(int *color_ptr)
{
	*color_ptr >>= 1;
	*color_ptr &= (127 << 16 | 127 << 8 | 127);
	return (1);
}