/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 20:13:08 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int handle_keyrelease(int keysym, t_data * data)
{
	if (keysym == 119)
    {
        data->w = 0;
    }
    if (keysym == 97)
	{
        data->a = 0;
    }
    
	if (keysym == 115)
	{
        data->s = 0;
    }	
    if (keysym == 100)
	{
        data->d = 0;
    }
    if (keysym == 65363)
    {
        data->r = 0;
    }
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
        int i = -1;
        while (++i < 4)
        {
            mlx_destroy_image(data->mlx_ptr, data->img[i].img_ptr);
        }
        mlx_destroy_image(data->mlx_ptr, data->screen.img_ptr);
        free_2d(data->map);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
		exit(100);
    }
	if (keysym == 119)
    {
        data->w = 1;
    }
    if (keysym == 97)
	{
        data->a = 1;
    }
    
	if (keysym == 115)
	{
        data->s = 1;
    }	
    if (keysym == 100)
	{
        data->d = 1;
    }
    if (keysym == 65363)
    {
        data->r = 1;
    }
    if (keysym == 65361)
    {
        data->l = 1;
    }
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
        return (free(data.mlx_ptr), ERROR_PARSING);
    ft_printf_2d(data.map);
    data.screen.img_ptr = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (data.screen.img_ptr == NULL)
        return (1);// destroy
    data.screen.addr = mlx_get_data_addr(data.screen.img_ptr, &data.screen.bits_per_pixel, &data.screen.size_line, &data.screen.endian);
    if (data.screen.addr == NULL)
        return (1);// destroy
    data.w = 0;
    data.a = 0;
    data.s = 0;
    data.d = 0;
    data.l = 0;
    data.r = 0;
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
    mlx_loop_hook(data.mlx_ptr, &ft_raycast, &data);
    mlx_loop(data.mlx_ptr);
   
    int i = -1;
    while (++i < 4)
    {
        mlx_destroy_image(data.mlx_ptr, data.img[i].img_ptr);
    }
    mlx_destroy_window(data.mlx_ptr, data.win_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free_2d(data.map);
    return (0);
}