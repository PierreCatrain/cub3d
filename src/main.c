/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/17 20:16:08 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
		exit(100);
	if (keysym == 119 && data->map[(int)(data->posX)][(int)(data->posY + 0.2)] != '1')
        data->posY += 0.1;
	if (keysym == 97 && data->map[(int)(data->posX - 0.2)][(int)(data->posY)] != '1')
		data->posX -= 0.1;
	if (keysym == 115 && data->map[(int)(data->posX)][(int)(data->posY - 0.2)] != '1')
		data->posY -= 0.1;
	if (keysym == 100 && data->map[(int)(data->posX + 0.2)][(int)(data->posY)] != '1')
		data->posX += 0.1;
    if (keysym == 65363)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(-1) - data->dirY * sin(-1);
        data->dirY = oldDirX * sin(-1) + data->dirY * cos(-1);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(-1) - data->planeY * sin(-1);
        data->planeY = oldPlaneX * sin(-1) + data->planeY * cos(-1);
    }
    if (keysym == 65361)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(1) - data->dirY * sin(1);
        data->dirY = oldDirX * sin(1) + data->dirY * cos(1);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(1) - data->planeY * sin(1);
        data->planeY = oldPlaneX * sin(1) + data->planeY * cos(1);
        // printf("%f et %f\n", data->dirX, oldDirX);   
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
    data.screen.img_ptr = mlx_new_image(data.mlx_ptr, 500, 500);
    if (data.screen.img_ptr == NULL)
        return (1);// destroy
    data.screen.addr = mlx_get_data_addr(data.screen.img_ptr, &data.screen.bits_per_pixel, &data.screen.size_line, &data.screen.endian);
    if (data.screen.addr == NULL)
        return (1);// destroy
    data.posX = data.start.x;
    data.posY = data.start.y;
    data.dirX = 0;
    data.dirY = 1;
    data.planeX = 0.66;
    data.planeY = 0;
    ft_raycast(&data);
    // ft_raycast(data);
    // while (1)
    //     usleep(200);
    // mlx_loop_hook(data.mlx_ptr, &ft_raycast, &data);
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