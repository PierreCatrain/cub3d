/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:05:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 20:35:50 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int    ft_check_coma(char *str)
{
    int    i;

    i = 0;
    if (ft_occ(str, ',') < 2)
        return (0);
    if (str[0] == ',')
        return (0);
    while (str[i])
    {
        if (i >= 1 && str[i] == ',' && str[i - 1] == ',')
            return (0);
        i++;
    }
    if (str[i - 1] == ',')
        return (0);
    return (1);
}

int	ft_transfo_color(int *hexa, char *entry, t_data *data)
{
	static int	passage = -1;
	char		**rgb;
	int			index;
	int			rgb_int[3];

	passage++;
	if (ft_check_coma(entry) == 0)
		return (ERROR);
	rgb = ft_split(entry, ",");
	if (rgb == NULL)
		return (ERROR);
	if (ft_strlen_2d(rgb) != 3)
		return (free_2d(rgb), ERROR);
	index = 0;
	while (index < 3)
	{
		rgb_int[index] = ft_atoi_hexa(rgb[index]);
		if (rgb_int[index] == ERROR_ATOI_HEXA)
			return (free_2d(rgb), ERROR);
		data->rgb[passage][index] = rgb_int[index];
		index++;
	}
	*hexa = (rgb_int[0] << 16) + (rgb_int[1] << 8) + rgb_int[2];
	return (free_2d(rgb), SUCCESS);
}

int	ft_get_color(char **split[6], t_data *data)
{
	int	index;

	index = 4;
	while (index <= 5)
	{
		if (ft_transfo_color(&data->color[index - 4], \
					split[index][1], data) != SUCCESS)
			return (ERROR);
		index++;
	}
	return (SUCCESS);
}

int	ft_set_new_img(t_img *tmp, t_data *data, t_img *img)
{
	tmp->img_ptr = mlx_new_image(data->mlx_ptr, SIZE_IMG, SIZE_IMG);
	if (tmp->img_ptr == NULL)
		return (ERROR);
	tmp->addr = mlx_get_data_addr(tmp->img_ptr, &tmp->bits_per_pixel, \
			&tmp->size_line, &tmp->endian);
	if (tmp->addr == NULL)
		return (ERROR);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
			&img->size_line, &img->endian);
	if (img->addr == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	ft_new_img(t_img *img, t_data *data, int x, int y)
{
	t_img	tmp;
	int		index;
	int		index_actual;

	if (ft_set_new_img(&tmp, data, img) == ERROR)
		return (ERROR);
	while (++x < SIZE_IMG)
	{
		y = -1;
		while (++y < SIZE_IMG)
		{
			index = (y * tmp.size_line) + (x * (tmp.bits_per_pixel / 8));
			index_actual = ((int)(y * ((double)img->height / \
				SIZE_IMG))*img->size_line) + \
					((int)(x * ((double)img->width / \
						SIZE_IMG))*(img->bits_per_pixel / 8));
			tmp.addr[index] = img->addr[index_actual];
			tmp.addr[index + 1] = img->addr[index_actual + 1];
			tmp.addr[index + 2] = img->addr[index_actual + 2];
		}
	}
	mlx_destroy_image(data->mlx_ptr, img->img_ptr);
	*img = tmp;
	return (SUCCESS);
}

int	ft_redimension_img(t_img img[4], t_data *data)
{
	int	index;

	index = -1;
	while (++index < 4)
	{
		if (ft_new_img(&img[index], data, -1, -1) != SUCCESS)
			return (ft_free_all_img_except_null(img), ERROR);
		img[index].height = SIZE_IMG;
		img[index].width = SIZE_IMG;
	}
	return (SUCCESS);
}
