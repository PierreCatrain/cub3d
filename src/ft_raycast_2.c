/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:13:23 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 21:13:39 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_where_to_draw(t_ray *ray, t_data data)
{
    if (ray->side == 0)
        ray->perpWallDist = ((double)ray->mapX - data.posX + (1 - (double)ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = ((double)ray->mapY - data.posY + (1 - (double)ray->stepY) / 2) / ray->rayDirY;

    
    ray->h = WINDOW_HEIGHT;
    ray->lineHeight = (int)(ray->h / ray->perpWallDist);


    ray->drawStart = -ray->lineHeight / 2 + ray->h / 2;
    ray->drawEnd = ray->lineHeight / 2 + ray->h / 2;
}

void ft_which_texture(t_ray *ray, t_data data)
{
    ray->wallX = 0;;
    if (ray->side == 0)
        ray->wallX = data.posY + (ray->perpWallDist * ray->rayDirY);
    else
        ray->wallX = data.posX + (ray->perpWallDist * ray->rayDirX);
    ray->wallX -= floor((ray->wallX));

    ray->texX = (int)(ray->wallX * (double)(SIZE_IMG));
    if(ray->side == 0 && ray->rayDirX > 0)
        ray->texX = SIZE_IMG - ray->texX - 1;
    else if(ray->side == 1 && ray->rayDirY < 0)
        ray->texX = SIZE_IMG - ray->texX - 1;
    ray->texture = 0;
    if (ray->side == 0 && ray->rayDirX < 0)
        ray->texture = NORTH;
    else if (ray->side == 0)
        ray->texture = SOUTH;
    else if (ray->side == 1 && ray->rayDirY < 0)
        ray->texture = WEST;
    else if (ray->side == 1)
        ray->texture = EAST;
}

void ft_complete_screen(t_ray *ray, t_data *data)
{
    ray->step = (double)SIZE_IMG / ray->lineHeight;
    ray->texY = 0;
    ray->tmp = 0.0;
    for(int y = ray->drawStart; y < ray->drawEnd; y++)
    {
        ray->tmp += ray->step;
        ray->texY = (int)ray->tmp;
        if (y >= 0 && y <= WINDOW_HEIGHT - 1)
        {
            data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * ray->x)] = data->img[ray->texture].addr[(SIZE_IMG * ray->texY * 4) + (ray->texX * 4)];
            data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * ray->x) + 1] = data->img[ray->texture].addr[(SIZE_IMG * ray->texY * 4) + (ray->texX * 4) + 1];
            data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * ray->x) + 2] = data->img[ray->texture].addr[(SIZE_IMG * ray->texY * 4) + (ray->texX * 4) + 2];
        }
    }
}