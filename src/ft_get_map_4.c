/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:24:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 05:15:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_border(t_data *data)
{
	char	**cpy;

	if (ft_cpy_with_frame(data->map, &cpy, ft_get_max_x(data->map) + 1, \
				ft_get_max_y(data->map) + 1) != SUCCESS)
		return (ERROR);
	if (ft_is_close_and_one_block(data, cpy) != SUCCESS)
		return (free_2d(cpy), ERROR);
	return (free_2d(cpy), SUCCESS);
}

int	ft_already_add(t_coord *coord, int x, int y)
{
	while (coord != NULL)
	{
		if (coord->x == x && coord->y == y)
			return (1);
		if (coord->next == NULL)
			break;
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

int	ft_is_outside(int x, int y, char **map)
{
	if (ft_occ(" .", map[x + 1][y]) == 1)
		return (ERROR);
	if (ft_occ(" .", map[x - 1][y]) == 1)
		return (ERROR);
	if (ft_occ(" .", map[x][y + 1]) == 1)
		return (ERROR);
	if (ft_occ(" .", map[x][y - 1]) == 1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_get_coord(t_coord **coord, int x, int y, char **map)
{
	if (ft_occ(" .1", map[x + 1][y]) == 0 && ft_already_add(*coord, x + 1, y) == 0)
	{
		if (ft_add_back_coord(coord, ft_new_coord(x + 1, y)) != SUCCESS)
			return (ERROR);
		if (ft_get_coord(coord, x + 1, y, map) != SUCCESS)
			return (ERROR);
	}
	if (ft_occ(" .1", map[x - 1][y]) == 0 && ft_already_add(*coord, x - 1, y) == 0)
	{
		if (ft_add_back_coord(coord, ft_new_coord(x - 1, y)) != SUCCESS)
 			return (ERROR);
		if (ft_get_coord(coord, x - 1, y, map) != SUCCESS)
			return (ERROR);
	}
	if (ft_occ(" .1", map[x][y + 1]) == 0 && ft_already_add(*coord, x, y + 1) == 0)
	{
		if (ft_add_back_coord(coord, ft_new_coord(x, y + 1)) != SUCCESS)
			return (ERROR);
		if (ft_get_coord(coord, x, y + 1, map) != SUCCESS)
			return (ERROR);
	}	
	if (ft_occ(" .1", map[x][y - 1]) == 0 && ft_already_add(*coord, x, y - 1) == 0)
	{
		if (ft_add_back_coord(coord, ft_new_coord(x, y - 1)) != SUCCESS)
			return (ERROR);
		if (ft_get_coord(coord, x, y - 1, map) != SUCCESS)
			return (ERROR);
	}
	return (ft_is_outside(x, y, map));
}

int	ft_is_close_and_one_block(t_data *data, char **cpy)
{
	t_coord	*coord;
	int	len;

	coord = NULL;
	if (ft_add_back_coord(&coord, ft_new_coord(data->posX + 1, data->posY + 1)) != SUCCESS)
		return (ERROR);
	if (ft_get_coord(&coord, data->posX + 1, data->posY + 1, cpy) != SUCCESS)
		return (ft_free_coord(coord), ERROR);
	len = 0;
	while (coord != NULL)
	{
		len++;
		if (coord->next == NULL)
			break;
		coord = coord->next;
	}
	if (len != ft_nb_case(data->map))
		return (ft_free_coord(coord), ERROR);
	return (ft_free_coord(coord), SUCCESS);
}
