/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:30 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/19 01:14:56 by picatrai         ###   ########.fr       */
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
        index_actual = ((int)(y * ((float)data->img[texture].height / SIZE_IMG)) * data->img[texture].size_line) + ((int)(texPos * ((float)data->img[texture].width / SIZE_IMG)) * (data->img[texture].bits_per_pixel / 8));
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

int ft_raycast(t_data *data)
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

    int w = WINDOW_WIDTH;
    int x = -1;
    while (++x < WINDOW_WIDTH)
    {
        double cameraX = 2 * x / (double)w - 1;
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
        
        if(side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;

        int h = WINDOW_HEIGHT;
        int lineHeight = (int)((double)(0.5 * h) / perpWallDist);


        int drawStart = -lineHeight / 2 + h / 2;
        int drawEnd = lineHeight / 2 + h / 2;
        if(drawStart < 0)
            drawStart = 0;
        if(drawEnd >= h)
            drawEnd = h - 1;
        
        int color = 62;
        if(side == 1)
            color = color / 2;
        ft_drawline(x, drawStart, drawEnd, color, data);
 
        // //calculer la valeur de wallX
        // double wallX ; //où exactement le mur a été touché
        // if (side == 0)
        //     wallX = data->posY + perpWallDist * rayDirY;
        // else
        //     wallX = data->posX + perpWallDist * rayDirX;
        // // printf("%f et %d\n", wallX, x);
        // wallX -= floor((wallX));

        // //coordonnée x sur la texture
        // int texX = (int)(wallX * (double)(SIZE_IMG));
        // if(side == 0 && rayDirX > 0)
        //     texX = SIZE_IMG - texX - 1;
        // if(side == 1 && rayDirY < 0)
        //     texX = SIZE_IMG - texX - 1;
        // // ft_drawline(texX, drawStart, drawEnd, color, data);

        //       // How much to increase the texture coordinate per screen pixel
        // double step = 1.0 * SIZE_IMG / lineHeight;
        // // Starting texture coordinate
        // double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
        // // for(int y = drawStart; y < drawEnd; y++)
        // // {
        // //     // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        // //     int texY = (int)texPos & (SIZE_IMG - 1);
        // //     texPos += step;
        // //     unsigned int color = texture[texNum][SIZE_IMG * texY + texX];
        // //     //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        // //     if(side == 1) color = (color >> 1) & 8355711;
        // //         buffer[y][x] = color;
        // // }
        // // printf("%f et %f et %d\n", wallX, texPos, x);
        // // printf("%d et %d et %d et %d\n", texPos, y, drawStart, drawEnd);
        // // if (side == 0)
        // //     ft_drawline_texture(texX, drawStart, drawEnd, data, NORTH);
        // // else if (side == 1)
        // //     ft_drawline_texture(texX, drawStart, drawEnd, data, EAST);
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen.img_ptr, 0, 0);
    return (0);
}