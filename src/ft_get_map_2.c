/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:19:37 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 19:59:41 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_get_start_data_core(t_data *data, int index, int index_mini)
{
	data->pos_x = index + 0.5;
	data->pos_y = index_mini + 0.5;
	if (data->map[index][index_mini] == 'N')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	if (data->map[index][index_mini] == 'S')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
	if (data->map[index][index_mini] == 'E')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
}

void	ft_get_start_data(t_data *data)
{
	int	index;
	int	index_mini;

	index = -1;
	while (data->map[++index])
	{
		index_mini = -1;
		while (data->map[index][++index_mini])
		{
			if (ft_occ("NSEW", data->map[index][index_mini]) != 0)
			{
				ft_get_start_data_core(data, index, index_mini);
				if (data->map[index][index_mini] == 'W')
				{
					data->dir_x = 0;
					data->dir_y = -1;
					data->plane_x = -0.66;
					data->plane_y = 0;
				}
				data->map[index][index_mini] = '0';
				return ;
			}
		}
	}
}

int	ft_only_one_player(char **map)
{
	int	index;
	int	index_mini;
	int	count;

	count = 0;
	index = -1;
	while (map[++index])
	{
		index_mini = -1;
		while (map[index][++index_mini])
		{
			if (ft_occ("NSEW", map[index][index_mini]) != 0)
				count++;
		}
	}
	if (count != 1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_condtion_no_unknown_character(char **map, char *charset)
{
	int	index;
	int	mini_index;

	index = -1;
	while (map[++index])
	{
		mini_index = -1;
		while (map[index][++mini_index])
		{
			if (ft_occ(charset, map[index][mini_index]) == 0)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_condition_no_line_empty(char **map)
{
	int	index;

	index = 0;
	while (map[index])
	{
		if (map[index][0] == '\n')
			return (ERROR);
		index++;
	}
	return (SUCCESS);
}
