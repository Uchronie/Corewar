/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_ws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 06:29:09 by gudemare          #+#    #+#             */
/*   Updated: 2018/02/26 06:29:47 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_str_ws(char *str)
{
	while (*str)
	{
		if (!(ft_is_whitespace(*str)))
			return (0);
		str++;
	}
	return (1);
}
