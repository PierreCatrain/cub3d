/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/18 23:45:09 by lgarfi           ###   ########.fr       */
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

void	ft_raycast(t_ray *ray, t_data data, char **map)
{
	double planeX = 0, planeY = 0.66;

	ray->posX = 20;
	ray->posY = 2;
	ray->raydirX = -1;
	ray->raydirY = 0;
	int		x;
	int		w = 500;
	double	h;
	x = -1;
	while (++x < w)
	{
		ray->cameraX = 2 * x / (double) w - 1;
		ray->raydirX = ray->dirX + planeX * ray->cameraX;
		ray->raydirY = ray->dirY + planeY * ray->cameraX;
		if (ray->raydirX == 0)
			ray->deltaDistX = 1e30;
		else
			ray->deltaDistX = fabs(1 / ray->raydirX);
		if (ray->raydirY == 0)
			ray->deltaDistY = 1e30;
		else
			ray->deltaDistY = fabs(1 / ray->raydirY);
		ray->mapX = (int) ray->posX;
		ray->mapY = (int) ray->posY;
		if (ray->raydirX < 0)
		{
			ray->stepX = -1;
			ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
		}
		else
		{
			ray->stepX = 1;
			ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
		}
		if (ray->raydirY < 0)
		{
			ray->stepY = -1;
			ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
		}
		else
		{
			ray->stepY = 1;
			ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
		}
		ray->hit = 0;
		while (ray->hit == 0)
		{
			if (ray->sideDistX < ray->sideDistY)
			{
				ray->sideDistX += ray->deltaDistX;
				ray->mapX += ray->stepX;
				ray->side = 0;
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				ray->mapY += ray->stepY;
				ray->side = 1;
			}
			if (map[ray->mapX][ray->mapY] > '0')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perpwallDist = ray->sideDistX - ray->deltaDistX;
		else
			ray->perpwallDist = ray->sideDistY - ray->deltaDistY;
		h = w;
		ray->lineHeight = (int) (h / ray->perpwallDist);
		ray->drawStart = -ray->lineHeight / 2 + h / 2;
		if (ray->drawStart < 0)
			ray->drawStart = 0;
		ray->drawEnd = ray->lineHeight / 2 + h / 2;
		if (ray->drawEnd >= h)
			ray->drawEnd = h - 1;
		ft_draw_line(ray->drawStart, ray->drawEnd, data, x);
	}
}

int	key_handler(int keysim, t_ray *ray)
{
	(void)ray;
	printf("kc %d\n", keysim);
	if (keysim == 119) // avance
	{
		if (ray->map[(int) (ray->posX + ray->dirX * 0.1)][(int) ray->posY] == 0)
			ray->posX += ray->dirX * 0.1;
		if (ray->map[(int) ray->posX][(int) (ray->posY + ray->dirY * 0.1)] == 0)
			ray->posY += ray->dirY * 0.1;
	}
	return (0);
}

int	ft_events(t_data *data, t_ray *ray)
{
	// mlx_hook(&data->win_ptr, ButtonPress, ButtonPressMask, &key_handler, ray);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &key_handler, ray);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_data	data;
	t_ray	ray;

	// int worldMap[ROWS][COLS] =
	// {
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };

	// ray.map = worldMap;
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

	ray.map = data.pas_ma_map;
    ft_raycast(&ray, data, ray.map);
	ft_events(&data, &ray);
	mlx_loop(data.mlx_ptr);
    //les truc a free ou destroy
    free(data.img[0].img_ptr);
    free(data.img[1].img_ptr);
    free(data.img[2].img_ptr);
    free(data.img[3].img_ptr);
    free_2d(data.pas_ma_map);
    free(data.win_ptr);
    free(data.mlx_ptr);
    printf("sort");
    return (0);
}