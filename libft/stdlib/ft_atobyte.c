/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atobyte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:45:20 by jremy             #+#    #+#             */
/*   Updated: 2022/07/04 18:32:28 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	__check_overflow(unsigned long result)
{
	if (result > 255)
		return (1);
	return (0);
}

int	__atobyte(const char *nb, int *res)
{
	unsigned long	result;
	int				i;

	i = 0;
	result = 0;
	while (__isdigit(nb[i]) && nb[i])
	{
		result = result * 10 + (nb[i] - '0');
		if (__check_overflow(result))
			return (0);
		i++;
	}
	if (nb[i] != 0)
		return (0);
	*res = (int)result;
	return (1);
}
