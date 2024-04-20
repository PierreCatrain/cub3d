/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:30 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 20:12:41 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void    ft_put_my_pixel(t_data *data, int x, int y, int color)
{
    int index;
    
    (void)color;
    index = ((y * (data->screen.size_line / 4)) + x) * 4;
    data->screen.addr[index] = color;
    data->screen.addr[index + 1] = color;
    data->screen.addr[index + 2] = color;
    data->screen.addr[index + 3] = 0;
}

void    ft_drawline_texture(int texPos, int drawStart, int drawEnd, t_data *data, int texture)
{
    int y;
    int index;
    int index_actual;

    y = drawStart - 1;
    while (++y < drawEnd)
    {
        index = (y * data->screen.size_line) + (texPos * (data->screen.bits_per_pixel / 8));
        index_actual = ((int)(y * ((double)data->img[texture].height / SIZE_IMG)) * data->img[texture].size_line) + ((int)(texPos * ((double)data->img[texture].width / SIZE_IMG)) * (data->img[texture].bits_per_pixel / 8));
        data->screen.addr[index] = 100;
        data->screen.addr[index + 1] = 100;
        data->screen.addr[index + 2] = 100;
    }
}

void ft_drawline(int x, int drawStart, int drawEnd, int color, t_data *data)
{
    while (drawStart < drawEnd)
    {
        ft_put_my_pixel(data, x, drawStart, color);
        drawStart++;
    }
}

void ft_key_manage(t_data *data)
{
    double moveSpeed = 0.01;
    double hitbox = 3;
    double rotSpeed = 0.004;
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

int ft_raycast(t_data *data)
{
    ft_key_manage(data);
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

    int w = WINDOW_WIDTH;
    int x = -1;
    while (++x < WINDOW_WIDTH)
    {
        double cameraX = (2 * x) / (double)w - 1.0;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = sqrt((1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)));
        double deltaDistY = sqrt((1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)));
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }
        while (hit == 0)
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if(data->map[mapX][mapY] == '1')
                hit = 1;
        }
        

        if (side == 0)
            perpWallDist = ((double)mapX - data->posX + (1 - (double)stepX) / 2) / rayDirX;
        else
            perpWallDist = ((double)mapY - data->posY + (1 - (double)stepY) / 2) / rayDirY;

        
        int h = WINDOW_HEIGHT;
        int lineHeight = (int)(h / perpWallDist);


        int drawStart = -lineHeight / 2 + h / 2;
        int drawEnd = lineHeight / 2 + h / 2;
        
        int color = 62;
        if(side == 1)
            color = color / 2;

        double wallX;
        if (side == 0)
            wallX = data->posY + (perpWallDist * rayDirY);
        else
            wallX = data->posX + (perpWallDist * rayDirX);
        wallX -= floor((wallX));

        int texX = (int)(wallX * (double)(SIZE_IMG));
        if(side == 0 && rayDirX > 0)
            texX = SIZE_IMG - texX - 1;
        else if(side == 1 && rayDirY < 0)
            texX = SIZE_IMG - texX - 1;
        int texture;
        if (side == 0 && rayDirX < 0)
            texture = NORTH;
        else if (side == 0)
            texture = SOUTH;
        else if (side == 1 && rayDirY < 0)
            texture = WEST;
        else if (side == 1)
            texture = EAST;

        double step = (double)SIZE_IMG / lineHeight;
        int texY = 0;
        double tmp = 0.0;
        for(int y = drawStart; y < drawEnd; y++)
        {
            tmp += step;
            texY = (int)tmp;
            if (y >= 0 && y <= WINDOW_HEIGHT - 1)
            {
                data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * x)] = data->img[texture].addr[(SIZE_IMG * texY * 4) + (texX * 4)];
                data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * x) + 1] = data->img[texture].addr[(SIZE_IMG * texY * 4) + (texX * 4) + 1];
                data->screen.addr[(y * WINDOW_WIDTH * 4) + (4 * x) + 2] = data->img[texture].addr[(SIZE_IMG * texY * 4) + (texX * 4) + 2];
            }
        }
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen.img_ptr, 0, 0);
    return (0);
}