/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:53:26 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 18:54:30 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	ft_atoi_hexa(char *str)
{
	long	resultat;
	int		i;

	i = 0;
	resultat = 0;
	if (str[i] == '-')
		return (ERROR_ATOI_HEXA);
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat *= 10;
		resultat += str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || resultat > 255)
		return (ERROR_ATOI_HEXA);
	return (resultat);
}
