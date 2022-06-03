/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   __tolower.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: jremy <jremy@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2021/11/23 16:53:37 by jremy #+##+# */
/*   Updated: 2022/01/10 15:04:51 by jremy###   ########.fr   */
/**/
/* ************************************************************************** */

#include "libft.h"

int	__tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
