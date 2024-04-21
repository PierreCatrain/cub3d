/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:54:48 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 04:02:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_line_empty(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] != ' ' && str[index] != '\t' && str[index] != '\n')
			return (0);
	}
	return (1);
}

int	ft_get_six_first_line(char **file, char ***six_line)
{
	int	index;
	int	mini_index;
	int	count;

	index = 0;
	mini_index = 0;
	count = 0;
	*six_line = malloc(sizeof(char *));
	if (*six_line == NULL)
		return (ERROR);
	(*six_line)[0] = NULL;
	while (file[index])
	{
		if (!ft_is_line_empty(file[index]))
		{
			*six_line = ft_add_to_2d(*six_line, file[index]);
			if (*six_line == NULL)
				return (ERROR);
			count++;
		}
		if (count == 6)
			break ;
		index++;
	}
	if (count != 6)
		return (free_2d(*six_line), ERROR);
	return (SUCCESS);
}

int	ft_get_texture_part_2(char **split[6], int *index, t_data *data)
{
	if (check_and_sort_split(split) != SUCCESS)
		return (free_mega_split(split, 6), ft_error("Error with value of texture\n"), ERROR);
	*index = -1;
	while (++(*index) < 4)
	{
		data->img[*index].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, (split)[*index][1], &data->img[*index].width, &data->img[*index].height);
		if (data->img[*index].img_ptr == NULL)
			return (ft_free_while_create_xpm(data, split, *index), ft_error("Error while creating image\n"), ERROR);
		data->img[*index].addr = NULL;
	}
	if (ft_redimension_img(data->img, data) != SUCCESS)
		return (free_mega_split(split, 6), ft_destroy_img(data, 4), ft_error("Error with redimension of image\n"), ERROR);
	if (ft_get_color(split, data) != SUCCESS)
		return (ft_free_while_create_xpm(data, split, 4), ft_destroy_img(data, 4), ft_error("Error with color\n"), ERROR);
	return (SUCCESS);
}

int	ft_get_texture(char **file, t_data *data)
{
	char	**six_line;
	char	**split[6];
	int	index;

	if (ft_get_six_first_line(file, &six_line) != SUCCESS)
		return (ft_error("Error with number of texture arguments\n"), ERROR);
	index = -1;
	while (++index < 6)
	{
		split[index] = ft_split(six_line[index], " \t\n");
		if (split[index] == NULL)
			return (free_2d(six_line), free_mega_split(split, index), ft_error("Error with malloc in ft_get_texture\n"), ERROR);
	}
	free_2d(six_line);
	if (ft_get_texture_part_2(split, &index, data) == ERROR)
		return (ERROR);
	return (free_mega_split(split, 6), SUCCESS);
}
