/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:01:37 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 18:15:08 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_swap(char **split[6], int index_1, int index_2)
{
	char	**tmp;

	tmp = split[index_1];
	split[index_1] = split[index_2];
	split[index_2] = tmp;
}

int	ft_find_index_split(char **split[6], char *find)
{
	int	index;

	index = -1;
	while (*split[++index])
	{
		if (!ft_strcmp(*split[index], find))
			return (index);
	}
	return (index);
}

int	ft_sort_split(char **split[6])
{
	if (ft_strcmp(split[0][0], "NO"))
		ft_swap(split, 0, ft_find_index_split(split, "NO"));
	if (ft_strcmp(split[1][0], "SO"))
		ft_swap(split, 1, ft_find_index_split(split, "SO"));
	if (ft_strcmp(split[2][0], "EA"))
		ft_swap(split, 2, ft_find_index_split(split, "EA"));
	if (ft_strcmp(split[3][0], "WE"))
		ft_swap(split, 3, ft_find_index_split(split, "WE"));
	if (ft_strcmp(split[4][0], "F"))
		ft_swap(split, 4, ft_find_index_split(split, "F"));
	if (ft_strcmp(split[5][0], "C"))
		ft_swap(split, 5, ft_find_index_split(split, "C"));
	return (SUCCESS);
}

void	check_and_sort_split_part_2(int (*tab)[6], char **split[6])
{
	int	index;

	index = -1;
	while (++index < 6)
	{
		if (!ft_strcmp(split[index][0], "NO"))
			(*tab)[NORTH] = 1;
		else if (!ft_strcmp(split[index][0], "SO"))
			(*tab)[SOUTH] = 1;
		else if (!ft_strcmp(split[index][0], "EA"))
			(*tab)[EAST] = 1;
		else if (!ft_strcmp(split[index][0], "WE"))
			(*tab)[WEST] = 1;
		else if (!ft_strcmp(split[index][0], "F"))
			(*tab)[FLOOR + 4] = 1;
		else if (!ft_strcmp(split[index][0], "C"))
			(*tab)[CELLING + 4] = 1;
	}
}

int	check_and_sort_split(char **split[6])
{
	int	index;
	int	tab[6];

	index = -1;
	while (++index < 6)
	{
		if (ft_strlen_2d(split[index]) != 2)
			return (ERROR);
		tab[index] = 0;
	}
	check_and_sort_split_part_2(&tab, split);
	index = -1;
	while (++index < 6)
	{
		if (tab[index] == 0)
		{
			return (ERROR);
		}
	}
	return (ft_sort_split(split));
}
