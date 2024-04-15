/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/27 15:04:08 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (envp[0] == NULL)
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