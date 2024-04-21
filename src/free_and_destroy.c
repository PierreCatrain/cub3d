/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:29:26 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 03:57:52 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_destroy_all_except_screen(t_data *data)
{
	int	i = -1;

	while (++i < 4)
		mlx_destroy_image(data->mlx_ptr, data->img[i].img_ptr);
	free_2d(data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

void	ft_destroy_all(t_data *data)
{
	int i = -1;

	while (++i < 4)
		mlx_destroy_image(data->mlx_ptr, data->img[i].img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->screen.img_ptr);
	free_2d(data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

int	ft_destroy_and_exit(t_data *data)
{
	int i = -1;

	while (++i < 4)
		mlx_destroy_image(data->mlx_ptr, data->img[i].img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->screen.img_ptr);
	free_2d(data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	free_2d(char **str)
{
	int	index;

	if (str == NULL)
		return ;
	if (str[0] == NULL)
	{
		free(str);
		return ;
	}
	index = -1;
	while (str[++index])
		free(str[index]);
	free(str);
}

void	free_mega_split(char **split[6], int index)
{
	while (--index >= 0)
		free_2d(split[index]);
}

void	ft_free_while_create_xpm(t_data *data, char **split[6], int index)
{
	while (--index >= 0)
		mlx_destroy_image(data->mlx_ptr, data->img[index].img_ptr);
	free_mega_split(split, 6);
}

void	ft_destroy_img(t_data *data, int index)
{
	int i = index;

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
