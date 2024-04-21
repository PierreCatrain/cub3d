/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:21:53 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 05:14:53 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_complete_with_frame(char *str, int max_y)
{
	char	*complete;
	int		index;

	complete = malloc(sizeof(char));
	if (complete == NULL)
		return (NULL);
	complete[0] = '\0';
	complete = ft_join_char(complete, '.');
	if (complete == NULL)
		return (NULL);
	index = -1;
	while (str[++index])
	{
		complete = ft_join_char(complete, str[index]);
		if (complete == NULL)
			return (NULL);
	}
	while (++index <= max_y)
	{
		complete = ft_join_char(complete, '.');
		if (complete == NULL)
			return (NULL);
	}
	return (complete);
}

int	ft_get_max_x(char **map)
{
	int	max_x;

	max_x = 0;
	while (map[max_x])
		max_x++;
	return (max_x);
}

int	ft_get_max_y(char **map)
{
	int	max_y;
	int	len;
	int	index;

	max_y = 0;
	index = -1;
	while (map[++index])
	{
		len = ft_strlen(map[index]);
		if (len > max_y)
			max_y = len;
	}
	return (max_y);
}

int	ft_set_cpy_with_frame(char ***cpy, int *x)
{
	*cpy = malloc(sizeof(char *));
	if (*cpy == NULL)
		return (ERROR);
	(*cpy)[0] = NULL;
	*x = -1;
	return (SUCCESS);
}

int	ft_cpy_with_frame(char **map, char ***cpy, int max_x, int max_y)
{
	char	*str;
	int		x;

	if (ft_set_cpy_with_frame(cpy, &x) == ERROR)
		return (ERROR);
	while (++x <= max_x)
	{
		if (x == 0 || x == max_x)
		{
			str = ft_complete_with_frame("", max_y);
			*cpy = ft_add_to_2d(*cpy, str);
			if (*cpy == NULL)
				return (free(str), ERROR);
			free(str);
		}
		else
		{
			str = ft_complete_with_frame(map[x - 1], max_y);
			*cpy = ft_add_to_2d(*cpy, str);
			if (*cpy == NULL)
				return (free(str), ERROR);
			free(str);
		}
	}
	return (SUCCESS);
}
