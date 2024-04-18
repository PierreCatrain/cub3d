/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/18 19:39:58 by lgarfi           ###   ########.fr       */
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

void	ft_raycast(t_ray *ray, t_data data, int map[24][24])
{
	double posX = 20, posY = 2;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;

	int		x;
	int		w = 500;
	double	h;
	x = -1;
	while (++x < w)
	{
		ray->cameraX = 2 * x / (double) w - 1;
		ray->raydirX = dirX + planeX * ray->cameraX;
		ray->raydirY = dirY + planeY * ray->cameraX;
		if (ray->raydirX == 0)
			ray->deltaDistX = 1e30;
		else
			ray->deltaDistX = fabs(1 / ray->raydirX);
		if (ray->raydirY == 0)
			ray->deltaDistY = 1e30;
		else
			ray->deltaDistY = fabs(1 / ray->raydirY);
		ray->mapX = (int) posX;
		ray->mapY = (int) posY;
		if (ray->raydirX < 0)
		{
			ray->stepX = -1;
			ray->sideDistX = (posX - ray->mapX) * ray->deltaDistX;
		}
		else
		{
			ray->stepX = 1;
			ray->sideDistX = (ray->mapX + 1.0 - posX) * ray->deltaDistX;
		}
		if (ray->raydirY < 0)
		{
			ray->stepY = -1;
			ray->sideDistY = (posY - ray->mapY) * ray->deltaDistY;
		}
		else
		{
			ray->stepY = 1;
			ray->sideDistY = (ray->mapY + 1.0 - posY) * ray->deltaDistY;
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
			if (map[ray->mapX][ray->mapY] > 0)
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

int	key_hook(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	printf("touche\n");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_data	data;
	t_ray	ray;
	
int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

    if (envp[0] == NULL)
		return (1);
    data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), ERROR);
    if (ft_parsing(argc, argv, &data) != SUCCESS)
        return (free(data.mlx_ptr), free(data.win_ptr), ERROR_PARSING);
	
    ft_raycast(&ray, data, worldMap);
	mlx_key_hook(data.win_ptr, key_hook, &data.vars);
	mlx_loop(data.mlx_ptr);
    //les truc a free ou destroy
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