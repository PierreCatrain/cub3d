/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:30 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 21:13:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_reset_screen(t_data *data)
{
    int index;
    for (int i = 0; i < WINDOW_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_HEIGHT; j++)
        {
            index = ((j * (data->screen.size_line / 4)) + i) * 4;
            if (j < WINDOW_HEIGHT / 2)
            {
                data->screen.addr[index] = (char)data->RGB[CELLING][2];
                data->screen.addr[index + 1] = (char)data->RGB[CELLING][1];
                data->screen.addr[index + 2] = (char)data->RGB[CELLING][0];
                data->screen.addr[index + 3] = 0;
            }
            else
            {
                data->screen.addr[index] = (char)data->RGB[FLOOR][2];
                data->screen.addr[index + 1] = (char)data->RGB[FLOOR][1];
                data->screen.addr[index + 2] = (char)data->RGB[FLOOR][0];
                data->screen.addr[index + 3] = 0;
            }
        }
    }
}

void ft_set_raycast(t_ray *ray, t_data data)
{
    ray->cameraX = (2 * ray->x) / (double)ray->w - 1.0;
    ray->rayDirX = data.dirX + data.planeX * ray->cameraX;
    ray->rayDirY = data.dirY + data.planeY * ray->cameraX;
    ray->mapX = (int)data.posX;
    ray->mapY = (int)data.posY;
    ray->sideDistX = 0;;
    ray->sideDistY = 0;
    ray->deltaDistX = sqrt((1 + (ray->rayDirY * ray->rayDirY) / (ray->rayDirX * ray->rayDirX)));
    ray->deltaDistY = sqrt((1 + (ray->rayDirX * ray->rayDirX) / (ray->rayDirY * ray->rayDirY)));
    ray->perpWallDist = 0;;
    ray->stepX = 0;;
    ray->stepY = 0;;
    ray->hit = 0;
    ray->side = 0;
}

void ft_calcul_side_dist(t_ray *ray, t_data data)
{
    if(ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (data.posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - data.posX) * ray->deltaDistX;
    }
    if(ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (data.posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - data.posY) * ray->deltaDistY;
    }
}

void    ft_increment_side_dist(t_ray *ray, t_data data)
{
    while (ray->hit == 0)
    {
        if(ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if(data.map[ray->mapX][ray->mapY] == '1')
            ray->hit = 1;
    }
}

int ft_raycast(t_data *data)
{
    t_ray ray;
    
    ft_key_manage(data);
    ft_reset_screen(data);

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
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen.img_ptr, 0, 0);
    return (0);
}