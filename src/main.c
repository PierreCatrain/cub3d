/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/18 20:47:04 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int handle_keypress(int keysym, t_data *data)
{
    double moveSpeed = 0.1;
    if (keysym == XK_Escape)
		exit(100);
	if (keysym == 119 && data->map[(int)(data->posX + data->dirX * 2 * moveSpeed)][(int)(data->posY + data->dirY * 2 * moveSpeed)] != '1')
    {
        data->posX += data->dirX * moveSpeed;
        data->posY += data->dirY * moveSpeed;
    }
    if (keysym == 97 && data->map[(int)(data->posX - data->dirY * 2 * moveSpeed)][(int)(data->posY + data->dirX * 2 * moveSpeed)] != '1')
	{
        data->posX -= data->dirY * moveSpeed;
        data->posY += data->dirX * moveSpeed;
    }
    
	if (keysym == 115 && data->map[(int)(data->posX - data->dirX * 2 * moveSpeed)][(int)(data->posY - data->dirY * 2 * moveSpeed)] != '1')
	{
        data->posX -= data->dirX * moveSpeed;
        data->posY -= data->dirY * moveSpeed;
    }	
    if (keysym == 100 && data->map[(int)(data->posX + data->dirY * 2 * moveSpeed)][(int)(data->posY - data->dirX * 2 * moveSpeed)] != '1')
	{
        data->posX += data->dirY * moveSpeed;
        data->posY -= data->dirX * moveSpeed;
    }
    if (keysym == 65363)
    {
        double val = -0.1;
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(val) - data->dirY * sin(val);
        data->dirY = oldDirX * sin(val) + data->dirY * cos(val);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(val) - data->planeY * sin(val);
        data->planeY = oldPlaneX * sin(val) + data->planeY * cos(val);
    }
    if (keysym == 65361)
    {
        double val = 0.1;
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(val) - data->dirY * sin(val);
        data->dirY = oldDirX * sin(val) + data->dirY * cos(val);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(val) - data->planeY * sin(val);
        data->planeY = oldPlaneX * sin(val) + data->planeY * cos(val);
    }
    ft_raycast(data);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (envp[0] == NULL)
        return (0);
    data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), ERROR);
    if (ft_parsing(argc, argv, &data) != SUCCESS)
        return (free(data.mlx_ptr), free(data.win_ptr), ERROR_PARSING);
    ft_printf_2d(data.map);
    data.screen.img_ptr = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (data.screen.img_ptr == NULL)
        return (1);// destroy
    data.screen.addr = mlx_get_data_addr(data.screen.img_ptr, &data.screen.bits_per_pixel, &data.screen.size_line, &data.screen.endian);
    if (data.screen.addr == NULL)
        return (1);// destroy
    ft_raycast(&data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_loop(data.mlx_ptr);
    //les truc a free ou destroy
    free(data.img[0].img_ptr);
    free(data.img[1].img_ptr);
    free(data.img[2].img_ptr);
    free(data.img[3].img_ptr);
    free_2d(data.map);
    free(data.win_ptr);
    free(data.mlx_ptr);
    return (0);
}