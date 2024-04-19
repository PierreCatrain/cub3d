/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/19 17:04:29 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_draw_line(int drawStart, int drawEnd, t_data data, int x)
{
	int	start = drawStart;
	int	end = drawEnd;

	while (start < end)
	{
		mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, start, 0x00FFFFFF);
		start++;
	}
}

void	ft_raycast(t_data *data, char **map)
{
	data->ray.posX = 20;
	data->ray.posY = 12;
	data->ray.raydirX = -1;
	data->ray.raydirY = 0;
	int		x;
	int		w = 500;
	double h;
	x = -1;
	data->ray.planeX = 0;
	data->ray.planeY = 0.66;
	while (++x < w)
	{
		data->ray.cameraX = 2 * x / (double) w - 1;
		data->ray.raydirX = data->ray.dirX + data->ray.planeX * data->ray.cameraX;
		data->ray.raydirY = data->ray.dirY + data->ray.planeY * data->ray.cameraX;
		if (data->ray.raydirX == 0)
			data->ray.deltaDistX = 1e30;
		else
			data->ray.deltaDistX = sqrt(1 + (data->ray.raydirY * data->ray.raydirY) / (data->ray.raydirX * data->ray.raydirX));

		if (data->ray.raydirY == 0)
			data->ray.deltaDistY = 1e30;
		else
			data->ray.deltaDistY = sqrt(1 + (data->ray.raydirX * data->ray.raydirX) / (data->ray.raydirY * data->ray.raydirY));
		data->ray.mapX = (int) data->ray.posX;
		data->ray.mapY = (int) data->ray.posY;
		printf("raydirX %f\n", data->ray.raydirX);
		if (data->ray.raydirX < 0)
		{
			data->ray.stepX = -1;
			data->ray.sideDistX = (data->ray.posX - data->ray.mapX) * data->ray.deltaDistX;
		}
		else
		{
			data->ray.stepX = 1;
			data->ray.sideDistX = (data->ray.mapX + 1.0 - data->ray.posX) * data->ray.deltaDistX;
		}
		if (data->ray.raydirY < 0)
		{
			data->ray.stepY = -1;
			data->ray.sideDistY = (data->ray.posY - data->ray.mapY) * data->ray.deltaDistY;
		}
		else
		{
			data->ray.stepY = 1;
			data->ray.sideDistY = (data->ray.mapY + 1.0 - data->ray.posY) * data->ray.deltaDistY;
		}
		data->ray.hit = 0;
		// printf("sideX %f | sideY %f | x %d\n", data->ray.raydirX, data->ray.raydirY, x);
		while (data->ray.hit == 0)
		{
			if (data->ray.sideDistX < data->ray.sideDistY)
			{
				data->ray.sideDistX += data->ray.deltaDistX;
				data->ray.mapX += data->ray.stepX;
				data->ray.side = 0;
			}
			else
			{
				data->ray.sideDistY += data->ray.deltaDistY;
				data->ray.mapY += data->ray.stepY;
				data->ray.side = 1;
			}
			// printf("mapX %d | mapY %d | x %d\n", data->ray.mapX, data->ray.mapY);
			if (map[data->ray.mapX][data->ray.mapY] > '0')
				data->ray.hit = 1;
		}
		if (data->ray.side == 0)
			data->ray.perpwallDist = data->ray.sideDistX - data->ray.deltaDistX;
		else
			data->ray.perpwallDist = data->ray.sideDistY - data->ray.deltaDistY;
		// printf("side = %d | perpwalldist %f | x %d\n",data->ray.side, data->ray.perpwallDist, x);
		h = w;
		data->ray.lineHeight = (int) (h / data->ray.perpwallDist);
		data->ray.drawStart = -data->ray.lineHeight / 2 + h / 2;
		if (data->ray.drawStart < 0)
			data->ray.drawStart = 0;
		data->ray.drawEnd = data->ray.lineHeight / 2 + h / 2;
		if (data->ray.drawEnd >= h)
			data->ray.drawEnd = h - 1;
		// printf("ds %d | de %d | x %d\n", data->ray.drawStart, data->ray.drawEnd, x);
		ft_draw_line(data->ray.drawStart, data->ray.drawEnd, *data, x);
	}
}

// int	key_handler(int keysim, t_ray *ray)
// {
// 	(void)ray;
// 	printf("kc %d\n", keysim);
// 	if (keysim == 119) // avance
// 	{
// 		if (data->map[(int) (data->ray.posX + data->ray.dirX * 0.1)][(int) data->ray.posY] == 0)
// 			data->posX += data->ray.dirX * 0.1;
// 		if (data->map[(int) data->ray.posX][(int) (data->ray.posY + data->ray.dirY * 0.1)] == 0)
// 			data->ray.posY += data->ray.dirY * 0.1;
// 	}
// 	return (0);
// }

// int	ft_events(t_data *data, t_ray *ray)
// {
// 	// mlx_hook(&data->win_ptr, ButtonPress, ButtonPressMask, &key_handler, ray);
// 	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &key_handler, ray);
// 	return (0);
// }

int main(int argc, char **argv, char **envp)
{
    t_data	data;

    if (envp[0] == NULL)
		return (1);
    data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), ERROR);
	if (ft_parsing(argc, argv, &data) != SUCCESS)
	{
		return (free(data.mlx_ptr), free(data.win_ptr), ERROR_PARSING);
	}

    ft_raycast(&data, data.map);
	// ft_events(&data, &ray);
	// mlx_loop(data.mlx_ptr);
    //les truc a free ou destroy
	sleep(2);
    free(data.img[0].img_ptr);
    free(data.img[1].img_ptr);
    free(data.img[2].img_ptr);
    free(data.img[3].img_ptr);
    free_2d(data.map);
    free(data.win_ptr);
    free(data.mlx_ptr);
    printf("sort");
    return (0);
}