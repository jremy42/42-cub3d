/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:46:35 by jremy             #+#    #+#             */
/*   Updated: 2022/07/04 09:48:42 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printer(void *content)
{
	__putstr_fd((char *) content, 2);
}

void	print_cub(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("text[%d] %s\n", i, (char *)cub->text[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		printf("color[%d] %s\n", i, (char *)cub->color[i]);
		i++;
	}
}
