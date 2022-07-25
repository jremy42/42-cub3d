/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:53:18 by deus              #+#    #+#             */
/*   Updated: 2022/07/25 15:01:38 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

t_list	*get_input(char **av)
{
	t_list	*new_input;
	t_list	*input;
	char	*r_readline;
	int		fd;
	int		ret;

	ret = 2;
	input = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		__exit_error_get_input("Open error", NULL, fd);
	while (ret > 0)
	{
		ret = sget_next_line(&r_readline, fd);
		if (ret == 0)
			break ;
		if (ret < 0)
			__exit_error_get_input("Malloc error", input, fd);
		new_input = __lstnew(r_readline);
		if (!new_input)
			__exit_error_get_input("Malloc error", input, fd);
		__lstadd_back(&input, new_input);
	}
	close(fd);
	return (input);
}

void	parsing(char **av, t_cub *cub)
{
	t_list	*input;

	input = get_input(av);
	cub->input = input;
	get_info(input, cub);
	if (!check_maps(cub))
		__exit_error(NULL, cub);
	if (!check_color(cub))
		__exit_error(NULL, cub);
	load_player_info(cub);
}
