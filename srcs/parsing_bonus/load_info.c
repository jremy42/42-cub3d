/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:41:12 by deus              #+#    #+#             */
/*   Updated: 2022/07/21 16:02:31 by jremy            ###   ########.fr       */
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
			__exit_error("malloc error", cub);
		if (size_split(ret) == 0)
		{
			free_split(ret);
			input = input->next;
			continue ;
		}
		if (size_split(ret) < 2 || size_split(ret) > 7)
			return (printf("[%s]\n", ret[0]), free_split(ret),
				__exit_error("wrong info format", cub));
		if (!load_info(ret, cub))
			return (free_split(ret), __exit_error("parsing error", cub));
		input = input->next;
	}
	if (!load_maps(input, cub))
		return (__exit_error("malloc error", cub));
}
