/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/17 22:15:59 by lgarfi           ###   ########.fr       */
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
	double posX = 1, posY = 12;
	double dirX = 0, dirY = 1;
	double planeX = 0, planeY = 0.66;

	int		x;
	int		w = 500;
	double	h = w;
	while (1)
	{
		x = -1;
		while (++x <= w)
		{
			ray->cameraX = 2 * x / (double) w - 1;
			ray->raydirX = dirX + planeX * ray->cameraX;
			ray->raydirY = dirY + planeY * ray->cameraX;
			if (ray->raydirX == 0)
				ray->raydirX = 1e30;
			if (ray->raydirY == 0)
				ray->raydirY = 1e30;
			printf("raydirX %f | raydirY %f | x %d\n", ray->raydirX, ray->raydirY, x);
			ray->deltaDistX = sqrt(1 + (ray->raydirY * ray->raydirY) / (ray->raydirX * ray->raydirX));
			ray->deltaDistY = sqrt(1 + (ray->raydirX * ray->raydirX) / (ray->raydirY * ray->raydirY));
			printf("deltaDistX %f | deltaDistY %f | x %d\n",ray->deltaDistX, ray->deltaDistY, x);
			ray->mapX = posX;
			ray->mapY = posY;
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
			printf("sideDistX %f | sideDistY %f | x %d\n", ray->sideDistX, ray->sideDistY, x);
			printf("steX %d | stepY %d\n", ray->stepX, ray->stepY);
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
				// printf("mapX %d | mapY %d | x %d\n", ray->mapX, ray->mapY, x);
				if (map[ray->mapX][ray->mapY] > '0')
					ray->hit = 1;
			}
			if (ray->side == 0)
				ray->perpwallDist = ray->sideDistX - ray->deltaDistX;
			else
				ray->perpwallDist = ray->sideDistY - ray->deltaDistY;
			ray->lineHeight = (int) (h / ray->perpwallDist);
			ray->drawStart = -ray->lineHeight / 2 + h / 2;
			if (ray->drawStart < 0)
				ray->drawStart = 0;
			ray->drawEnd = ray->lineHeight / 2 + h / 2;
			if (ray->drawEnd >= h)
				ray->drawEnd = h - 1;
			ft_draw_line(ray->drawStart, ray->drawEnd, data, x);
		}
		break ;
	}

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
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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
    while (1)
		;
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