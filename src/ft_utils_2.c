/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:45:25 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 17:58:06 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	index;

	index = 0;
	while (str1[index] && str2[index])
	{
		if (str1[index] != str2[index])
			break ;
		index++;
	}
	return (str1[index] - str2[index]);
}

void	ft_error(char *str)
{
	write(2, "ERROR\n", 6);
	write(2, str, ft_strlen(str));
}

int	ft_occ(char *str, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}

int	ft_already_add(t_coord *coord, int x, int y)
{
	while (coord != NULL)
	{
		if (coord->x == x && coord->y == y)
			return (1);
		if (coord->next == NULL)
			break ;
		coord = coord->next;
	}
	return (0);
}

int	ft_nb_case(char **map)
{
	int	count;
	int	index;
	int	mini_index;

	index = -1;
	count = 0;
	while (map[++index])
	{
		mini_index = -1;
		while (map[index][++mini_index])
		{
			if (ft_occ("NSEO0", map[index][mini_index]))
				count++;
		}
	}
	return (count);
}
