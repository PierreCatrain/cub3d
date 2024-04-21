/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_manage_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:36:53 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 19:38:01 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keyrelease(int keysym, t_data *data)
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

int	handle_keypress(int keysym, t_data *data)
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

int	ft_handle_mouse(int x, int y, t_data *data)
{
	int	width_third;

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
	return (0);
}
