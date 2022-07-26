/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:41:12 by deus              #+#    #+#             */
/*   Updated: 2022/07/26 11:54:41 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	get_info(t_list *input, t_cub *cub)
{
	char	**ret;
	char	*curent_string;

	while (input && missing_info_cub(cub))
	{
		curent_string = (char *)input->content;
		ret = __split_charset(curent_string, " \f\t\n\r\v");
		if (__strlen(curent_string) && !ret)
			__exit_error("Malloc error", cub);
		if (size_split(ret) == 0)
		{
			free_split(ret);
			input = input->next;
			continue ;
		}
		if (size_split(ret) != 2)
			return (free_split(ret),
				__exit_error("Wrong info format", cub));
		if (!load_info(ret, cub))
			return (free_split(ret), __exit_error(NULL, cub));
		input = input->next;
	}
	if (!load_maps(input, cub))
		return (__exit_error("Malloc error", cub));
}
