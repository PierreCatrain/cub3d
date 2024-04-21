/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:13:23 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 20:05:25 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_where_to_draw(t_ray *ray, t_data data)
{
	if (ray->side == 0)
		ray->perpwalldist = ((double)ray->map_x - data.pos_x + \
				(1 - (double)ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perpwalldist = ((double)ray->map_y - data.pos_y + \
				(1 - (double)ray->step_y) / 2) / ray->raydir_y;
	ray->h = WINDOW_HEIGHT;
	ray->lineheight = (int)(ray->h / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + ray->h / 2;
	ray->drawend = ray->lineheight / 2 + ray->h / 2;
}

void	ft_which_texture(t_ray *ray, t_data data)
{
	ray->wall_x = 0;
	if (ray->side == 0)
		ray->wall_x = data.pos_y + (ray->perpwalldist * ray->raydir_y);
	else
		ray->wall_x = data.pos_x + (ray->perpwalldist * ray->raydir_x);
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)(SIZE_IMG));
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->tex_x = SIZE_IMG - ray->tex_x - 1;
	else if (ray->side == 1 && ray->raydir_y < 0)
		ray->tex_x = SIZE_IMG - ray->tex_x - 1;
	ray->texture = 0;
	if (ray->side == 0 && ray->raydir_x < 0)
		ray->texture = NORTH;
	else if (ray->side == 0)
		ray->texture = SOUTH;
	else if (ray->side == 1 && ray->raydir_y < 0)
		ray->texture = WEST;
	else if (ray->side == 1)
		ray->texture = EAST;
}

void	ft_complete_screen(t_ray *ray, t_data *data)
{
	int	y;

	y = ray->drawstart - 1;
	ray->step = (double)SIZE_IMG / ray->lineheight;
	ray->tex_y = 0;
	ray->tmp = 0.0;
	while (++y < ray->drawend)
	{
		ray->tmp += ray->step;
		ray->tex_y = (int)ray->tmp;
		if (y >= 0 && y <= WINDOW_HEIGHT - 1)
		{
			data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * ray->x)] \
				= data->img[ray->texture].addr[(SIZE_IMG * \
						ray->tex_y * 4) + (ray->tex_x * 4)];
			data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * ray->x) \
				+ 1] = data->img[ray->texture].addr[(SIZE_IMG * \
						ray->tex_y * 4) + (ray->tex_x * 4) + 1];
			data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * ray->x) \
				+ 2] = data->img[ray->texture].addr[(SIZE_IMG * \
						ray->tex_y * 4) + (ray->tex_x * 4) + 2];
		}
	}
}
