/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 20:40:28 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_set_game(t_data *data)
{
	data->w = 0;
	data->a = 0;
	data->s = 0;
	data->d = 0;
	data->l = 0;
	data->r = 0;
	mlx_hook(data->win_ptr, 17, 0, &ft_destroy_and_exit, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, \
			&handle_keyrelease, data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, \
			&ft_handle_mouse, data);
	mlx_loop_hook(data->mlx_ptr, &ft_raycast, data);
	mlx_loop(data->mlx_ptr);
	ft_destroy_all(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (envp[0] == NULL)
		return (ft_error("Error with env\n"), ERROR);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), ERROR);
	if (ft_parsing(argc, argv, &data) != SUCCESS)
		return (ERROR_PARSING);
	data.screen.img_ptr = mlx_new_image(data.mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data.screen.img_ptr == NULL)
		return (ft_destroy_all_except_screen(&data), ERROR);
	data.screen.addr = mlx_get_data_addr(data.screen.img_ptr, \
			&data.screen.bits_per_pixel, &data.screen.size_line, \
			&data.screen.endian);
	if (data.screen.addr == NULL)
		return (ft_destroy_all(&data), ERROR);
	ft_set_game(&data);
	return (0);
}

//espace entre les virgules

