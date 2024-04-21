/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_manage_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:11:40 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 20:12:09 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_key_manage_part_1(t_data *data, double moveSpeed, double hitbox)
{
	if (data->w == 1 && data->map[(int)(data->pos_x + data->dir_x * hitbox * \
		moveSpeed)][(int)(data->pos_y + data->dir_y * hitbox * moveSpeed)] \
		!= '1' && data->map[(int)(data->pos_x - 0.05 + data->dir_x * \
		hitbox * moveSpeed)][(int)(data->pos_y - 0.05 + \
		data->dir_y * hitbox * moveSpeed)] != '1' && \
		data->map[(int)(data->pos_x + 0.05 + data->dir_x * hitbox * \
		moveSpeed)][(int)(data->pos_y + 0.05 + data->dir_y * hitbox * \
		moveSpeed)] != '1')
	{
		data->pos_x += data->dir_x * moveSpeed;
		data->pos_y += data->dir_y * moveSpeed;
	}
	if (data->a == 1 && data->map[(int)(data->pos_x - data->plane_x * hitbox * \
		moveSpeed)][(int)(data->pos_y - data->plane_y * hitbox * moveSpeed)] \
		!= '1' && data->map[(int)(data->pos_x - 0.05 - data->plane_x * \
		hitbox * moveSpeed)][(int)(data->pos_y - 0.05 - data->plane_y * \
		hitbox * moveSpeed)] != '1' && data->map[(int)(data->pos_x + 0.05 - \
		data->plane_x * hitbox * moveSpeed)][(int)(data->pos_y + 0.05 - \
		data->plane_y * hitbox * moveSpeed)] != '1')
	{
		data->pos_x -= data->plane_x * moveSpeed;
		data->pos_y -= data->plane_y * moveSpeed;
	}
}

void	ft_key_manage_part_2(t_data *data, double moveSpeed, double hitbox)
{
	if (data->s == 1 && data->map[(int)(data->pos_x - data->dir_x * hitbox * \
		moveSpeed)][(int)(data->pos_y - data->dir_y * hitbox * moveSpeed)] \
		!= '1' && data->map[(int)(data->pos_x - 0.05 - data->dir_x * hitbox * \
		moveSpeed)][(int)(data->pos_y - 0.05 - data->dir_y * hitbox * \
		moveSpeed)] != '1' && data->map[(int)(data->pos_x + 0.05 - \
		data->dir_x * hitbox * moveSpeed)][(int)(data->pos_y + 0.05 - \
		data->dir_y * hitbox * moveSpeed)] != '1')
	{
		data->pos_x -= data->dir_x * moveSpeed;
		data->pos_y -= data->dir_y * moveSpeed;
	}	
	if (data->d == 1 && data->map[(int)(data->pos_x + data->plane_x * hitbox * \
		moveSpeed)][(int)(data->pos_y + data->plane_y * hitbox * moveSpeed)] \
		!= '1' && data->map[(int)(data->pos_x - 0.05 + data->plane_x * hitbox * \
		moveSpeed)][(int)(data->pos_y - 0.05 + data->plane_y * hitbox * \
		moveSpeed)] != '1' && data->map[(int)(data->pos_x + 0.05 + \
		data->plane_x * hitbox * moveSpeed)][(int)(data->pos_y + 0.05 + \
		data->plane_y * hitbox * moveSpeed)] != '1')
	{
		data->pos_x += data->plane_x * moveSpeed;
		data->pos_y += data->plane_y * moveSpeed;
	}
}

void	ft_key_manage_part_3(t_data *data, double olddir_x, \
		double oldplane_x, double rotSpeed)
{
	if (data->r == 1)
	{
		olddir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-rotSpeed) - \
				data->dir_y * sin(-rotSpeed);
		data->dir_y = olddir_x * sin(-rotSpeed) + data->dir_y * cos(-rotSpeed);
		oldplane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-rotSpeed) - \
				data->plane_y * sin(-rotSpeed);
		data->plane_y = oldplane_x * sin(-rotSpeed) + \
				data->plane_y * cos(-rotSpeed);
	}
	if (data->l == 1)
	{
		olddir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(rotSpeed) - data->dir_y * sin(rotSpeed);
		data->dir_y = olddir_x * sin(rotSpeed) + data->dir_y * cos(rotSpeed);
		oldplane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(rotSpeed) - \
				data->plane_y * sin(rotSpeed);
		data->plane_y = oldplane_x * sin(rotSpeed) + \
				data->plane_y * cos(rotSpeed);
	}
}

void	ft_key_manage(t_data *data)
{
	double	move_speed;
	double	hitbox;
	double	rot_speed;

	move_speed = 0.01;
	hitbox = 3;
	rot_speed = 0.004;
	ft_key_manage_part_1(data, move_speed, hitbox);
	ft_key_manage_part_2(data, move_speed, hitbox);
	ft_key_manage_part_3(data, 0, 0, rot_speed);
}
