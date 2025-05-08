/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:55:55 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/05/08 16:55:55 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *number)
{
	int	i;

	i = -1;
	while (i++, number[i])
		if (!ft_isdigit(number[i]))
			return (1);
	return (0);
}
