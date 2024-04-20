/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:11:40 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 22:24:45 by picatrai         ###   ########.fr       */
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

int handle_keyrelease(int keysym, t_data * data)
{
	if (keysym == 119)
        data->w = 0;
    if (keysym == 97)
    {
        data->a = 0;
    }
	if (keysym == 115)
        data->s = 0;
    if (keysym == 100)
        data->d = 0;
    if (keysym == 65363)
        data->r = 0;
    if (keysym == 65361)
    {
        data->l = 0;
    }
	return (0);
}

int handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
    {
        ft_destroy_all(data);
		exit(0);
    }
	if (keysym == 119)
        data->w = 1;
    if (keysym == 97)
    {
        data->a = 1;
    }
	if (keysym == 115)
        data->s = 1;
    if (keysym == 100)
        data->d = 1;
    if (keysym == 65363)
        data->r = 1;
    if (keysym == 65361)
    {
        data->l = 1;
    }
	return (0);
}

int    ft_handle_mouse(int x, int y, t_data *data)
{
    int width_third;
    
    (void)y;
    width_third = WINDOW_WIDTH / 3;
    if (x < WINDOW_WIDTH / 3)
    {
        data->l = 1;
        data->r = 0;
    }
    else if (x > WINDOW_WIDTH - width_third)
    {
        data->l = 0;
        data->r = 1;
    }
    else
    {
        data->l = 0;
        data->r = 0;
    }
    // if (x == 0 || y == 0 || x == WINDOW_WIDTH - 1|| y == WINDOW_HEIGHT - 1)
    // {
    //     data->l = 0;
    //     data->r = 0;
    // }
    return (0);
}