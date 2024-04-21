/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:30 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 20:07:32 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_reset_screen(t_data *data, int i, int j)
{
	int	index;

	while (++i < WINDOW_WIDTH)
	{
		j = -1;
		while (++j < WINDOW_HEIGHT)
		{
			index = ((j * (data->screen.size_line / 4)) + i) * 4;
			if (j < WINDOW_HEIGHT / 2)
			{
				data->screen.addr[index] = (char)data->rgb[CELLING][2];
				data->screen.addr[index + 1] = (char)data->rgb[CELLING][1];
				data->screen.addr[index + 2] = (char)data->rgb[CELLING][0];
				data->screen.addr[index + 3] = 0;
			}
			else
			{
				data->screen.addr[index] = (char)data->rgb[FLOOR][2];
				data->screen.addr[index + 1] = (char)data->rgb[FLOOR][1];
				data->screen.addr[index + 2] = (char)data->rgb[FLOOR][0];
				data->screen.addr[index + 3] = 0;
			}
		}
	}
}

void	ft_set_raycast(t_ray *ray, t_data data)
{
	ray->camera_x = (2 * ray->x) / (double)ray->w - 1.0;
	ray->raydir_x = data.dir_x + data.plane_x * ray->camera_x;
	ray->raydir_y = data.dir_y + data.plane_y * ray->camera_x;
	ray->map_x = (int)data.pos_x;
	ray->map_y = (int)data.pos_y;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = sqrt((1 + (ray->raydir_y * ray->raydir_y) \
				/ (ray->raydir_x * ray->raydir_x)));
	ray->deltadist_y = sqrt((1 + (ray->raydir_x * ray->raydir_x) \
				/ (ray->raydir_y * ray->raydir_y)));
	ray->perpwalldist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
}

void	ft_calcul_side_dist(t_ray *ray, t_data data)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data.pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - data.pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data.pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data.pos_y) * ray->deltadist_y;
	}
}

void	ft_increment_side_dist(t_ray *ray, t_data data)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data.map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

int	ft_raycast(t_data *data)
{
	t_ray	ray;

	ft_key_manage(data);
	ft_reset_screen(data, -1, -1);
	ray.w = WINDOW_WIDTH;
	ray.x = -1;
	while (++ray.x < WINDOW_WIDTH)
	{
		ft_set_raycast(&ray, *data);
		ft_calcul_side_dist(&ray, *data);
		ft_increment_side_dist(&ray, *data);
		ft_where_to_draw(&ray, *data);
		ft_which_texture(&ray, *data);
		ft_complete_screen(&ray, data);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->screen.img_ptr, 0, 0);
	return (0);
}
