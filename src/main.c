/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/16 21:49:46 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_raycast(t_ray *ray)
{
	int	x;
	double rayDirX;
	double rayDirY;
	

	x = 0;
	ray->posX = 0;
	ray->posY = 0;
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
	while (x < 30)
	{
		ray->cameraX = 2 * x / 30 - 1;
		rayDirX = ray->dirX + ray->planeX * ray->cameraX;
		rayDirY = ray->dirY + ray->planeY * ray->cameraX;
		if (rayDirX == 0.0)
			rayDirX = 1e30;
		else if (rayDirY == 0.0)
			rayDirY = 1e30;
		ray->deltaDistX = abs(1 / rayDirX);
		ray->deltaDistY = abs(1 / rayDirY);
	}
}

int main(int argc, char **argv, char **envp)
{
    t_data	data;
	t_ray	ray;
	
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
    while (1)
        usleep(200);
	
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