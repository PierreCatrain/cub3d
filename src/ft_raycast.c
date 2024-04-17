/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:30 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/17 20:18:15 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void    ft_put_my_pixel(t_data *data, int x, int y, int color)
{
    int index;
    
    (void)color;
    index = ((y * (data->screen.size_line / 4)) + x) * 4;
    data->screen.addr[index] = 50;
    data->screen.addr[index + 1] = 50;
    data->screen.addr[index + 2] = 100;
}

void ft_drawline(int x, int drawStart, int drawEnd, int color, t_data *data)
{
    // drawEnd = drawStart + 2;
    while (drawStart < drawEnd)
    {
        ft_put_my_pixel(data, x, drawStart, color);
        // mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart, color);
        drawStart++;
        // printf("ici\n");
    }
    // mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, drawStart, color);
    // (void)drawEnd;
}

int ft_raycast(t_data *data)
{
    int index;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            index = ((j * (data->screen.size_line / 4)) + i) * 4;
            data->screen.addr[index] = 0;
            data->screen.addr[index + 1] = 0;
            data->screen.addr[index + 2] = 0;
            data->screen.addr[index + 3] = 1;
        }
    }
    double time = 0;
    double oldTime = 0;

    double tmp;
    
    tmp = 0;
    while (tmp < 1)
    {
        data->posX += tmp;
        tmp += 0.1;
        int w = 2 * data->planeX * 200;
        w = 500;
        for(int x = 0; x < 500; x++)
        {
        //calculate ray position and direction
        double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        //which box of the map we're in
        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = sqrt((1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)));
        double deltaDistY = sqrt((1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)));
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
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
        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
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
            //Check if ray has hit a wall
            if(data->map[mapX][mapY] == '1')
                hit = 1;
        }
        // printf("%d et %f et %f\n", x, sideDistX, sideDistY);

        //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
        if(side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);

        int h = 500;
        //Calculate height of line to draw on screen
        int lineHeight = (int)((double)(0.5 * h) / perpWallDist);


        // int pitch = 100;

            //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if(drawEnd >= h) drawEnd = h - 1;

        // printf("%d et %f et %f et %d et %f et %f\n", x, perpWallDist, perpWallDist, side, sideDistX, deltaDistX);
        //choose wall color
        int color;
        // printf("ici %c pour x %d et y %d\n", data.map[mapX][mapY], mapX, mapY);
        switch(data->map[mapX][mapY])
        {
            case 1:  color = data->color[FLOOR];    break; //red
            case 0:  color = data->color[CELLING];  break; //green
            default: color = data->color[FLOOR]; break; //yellow
        }

        //give x and y sides different brightness
        if(side == 1) {color = color / 2;}

        //draw the pixels of the stripe as a vertical line
        ft_drawline(x, drawStart, drawEnd, color, data);
        }
        // printf("ici\n");
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen.img_ptr, 0, 0);
        //timing for input and FPS counter
        oldTime = time;
        break ;
    }
    return (0);
}