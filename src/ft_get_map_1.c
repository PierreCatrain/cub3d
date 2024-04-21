/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:16:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 04:59:59 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_without_last_line_return(char *str)
{
	char	*new_str;
	int		index;

	index = 0;
	new_str = malloc(sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	while (str[index])
	{
		if (index == 0 || str[index] != '\n')
		{
			new_str = ft_join_char(new_str, str[index]);
			if (new_str == NULL)
				return (NULL);
		}
		index++;
	}
	return (new_str);
}

int	ft_get_map_without_start_end(char ***map, char **after_six, int index_start)
{
	char	*str;
	int		index_end;

	index_end = ft_strlen_2d(after_six) -1;
	while (after_six[index_start] && after_six[index_start][0] == '\n')
		index_start++;
	while (index_end > 0 && after_six[index_end][0] == '\n')
		index_end--;
	if (index_end <= index_start)
		return (ERROR);
	*map = malloc(sizeof(char *));
	if (*map == NULL)
		return (ERROR);
	(*map)[0] = NULL;
	while (after_six[index_start] && index_start <= index_end)
	{
		str = ft_without_last_line_return(after_six[index_start]);
		*map = ft_add_to_2d(*map, str);
		if (*map == NULL)
			return (free (str), ERROR);
		index_start++;
		free(str);
	}
	return (SUCCESS);
}

int	ft_get_after_six_line(char ***after_six, char **file)
{
	int	index;
	int	mini_index;
	int	count;

	index = 0;
	mini_index = 0;
	count = 0;
	*after_six = malloc(sizeof(char *));
	if (*after_six == NULL)
		return (ERROR);
	(*after_six)[0] = NULL;
	while (file[index])
	{
		if (count >= 6)
		{
			*after_six = ft_add_to_2d(*after_six, file[index]);
			if (*after_six == NULL)
				return (ERROR);
		}
		if (file[index][0] != '\n')
			count++;
		index++;
	}
	return (SUCCESS);
}

int	ft_get_after_six_line_without_start_end(char ***map, char **file)
{
	char	**after_six;

	if (ft_get_after_six_line(&after_six, file) != SUCCESS)
		return (ERROR);
	if (ft_get_map_without_start_end(map, after_six, 0) != SUCCESS)
		return (free_2d(after_six), ERROR);
	return (free_2d(after_six), SUCCESS);
}

int	ft_get_map(char **file, t_data *data)
{
	if (ft_get_after_six_line_without_start_end(&data->map, file) != SUCCESS)
		return (ft_error("Error with map\n"), ERROR);
	if (ft_condition_no_line_empty(data->map) != SUCCESS)
		return (free_2d(data->map), \
				ft_error("Error with map, a line is empty\n"), ERROR);
	if (ft_condtion_no_unknown_character(data->map, "10NSEW ") != SUCCESS)
		return (free_2d(data->map), \
				ft_error("Error with map, a character is unknown\n"), ERROR);
	if (ft_only_one_player(data->map) != SUCCESS)
		return (free_2d(data->map), \
				ft_error("Error with map, too many players\n"), ERROR);
	ft_get_start_data(data);
	if (ft_check_border(data) != SUCCESS)
		return (free_2d(data->map), \
				ft_error("Error with map, bad border\n"), ERROR);
	return (SUCCESS);
}
