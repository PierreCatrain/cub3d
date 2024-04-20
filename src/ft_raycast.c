/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:30 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 20:41:09 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_key_manage_part_1(t_data *data, double moveSpeed, double hitbox)
{
    if (data->w == 1 && data->map[(int)(data->posX + data->dirX * hitbox * moveSpeed)][(int)(data->posY + data->dirY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX - 0.05 + data->dirX * hitbox * moveSpeed)][(int)(data->posY - 0.05 + data->dirY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX + 0.05 + data->dirX * hitbox * moveSpeed)][(int)(data->posY + 0.05 + data->dirY * hitbox * moveSpeed)] != '1')
    {
        data->posX += data->dirX * moveSpeed;
        data->posY += data->dirY * moveSpeed;
    }
    if (data->a == 1 && data->map[(int)(data->posX - data->planeX * hitbox * moveSpeed)][(int)(data->posY - data->planeY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX - 0.05 - data->planeX * hitbox * moveSpeed)][(int)(data->posY - 0.05 - data->planeY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX + 0.05 - data->planeX * hitbox * moveSpeed)][(int)(data->posY + 0.05 - data->planeY * hitbox * moveSpeed)] != '1')
	{
        data->posX -= data->planeX * moveSpeed;
        data->posY -= data->planeY * moveSpeed;
    }
    
    if (data->s == 1 && data->map[(int)(data->posX - data->dirX * hitbox * moveSpeed)][(int)(data->posY - data->dirY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX - 0.05 - data->dirX * hitbox * moveSpeed)][(int)(data->posY - 0.05 - data->dirY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX + 0.05 - data->dirX * hitbox * moveSpeed)][(int)(data->posY + 0.05 - data->dirY * hitbox * moveSpeed)] != '1')
    {
        data->posX -= data->dirX * moveSpeed;
        data->posY -= data->dirY * moveSpeed;
    }	
    if (data->d == 1 && data->map[(int)(data->posX + data->planeX * hitbox * moveSpeed)][(int)(data->posY + data->planeY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX - 0.05 + data->planeX * hitbox * moveSpeed)][(int)(data->posY - 0.05 + data->planeY * hitbox * moveSpeed)] != '1' && data->map[(int)(data->posX + 0.05 + data->planeX * hitbox * moveSpeed)][(int)(data->posY + 0.05 + data->planeY * hitbox * moveSpeed)] != '1')
    {
        data->posX += data->planeX * moveSpeed;
        data->posY += data->planeY * moveSpeed;
    }
}

void ft_key_manage(t_data *data)
{
    double moveSpeed = 0.01;
    double hitbox = 3;
    double rotSpeed = 0.004;
    ft_key_manage_part_1(data, moveSpeed, hitbox);
    if (data->r == 1)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
        data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
        data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
    }
    if (data->l == 1)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
        data->dirY = oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
        data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
    }
}

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

// void ft_side_dist()
// {
//     if(rayDirX < 0)
//     {
//         stepX = -1;
//         sideDistX = (data->posX - mapX) * deltaDistX;
//     }
//     else
//     {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
//     }
//     if(rayDirY < 0)
//     {
//         stepY = -1;
//         sideDistY = (data->posY - mapY) * deltaDistY;
//     }
//     else
//     {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
//     }
// }

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