/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:58:41 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 19:00:01 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_while_create_xpm(t_data *data, char **split[6], int index)
{
	while (--index >= 0)
		mlx_destroy_image(data->mlx_ptr, data->img[index].img_ptr);
	free_mega_split(split, 6);
}

void	ft_destroy_img(t_data *data, int index)
{
	int	i;

	i = index;
	while (--i >= 0)
	{
		mlx_destroy_image(data->mlx_ptr, data->img[i].img_ptr);
	}
}

void	ft_free_all_img_except_null(t_img img[4])
{
	int	index;

	index = -1;
	while (++index < 4)
	{
		if (img[index].img_ptr != NULL)
			free(img[index].img_ptr);
		if (img[index].addr != NULL)
			free(img[index].addr);
	}
}

void	ft_destroy_mlx(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}
