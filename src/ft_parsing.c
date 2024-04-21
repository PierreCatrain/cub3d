/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:08:37 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 04:56:20 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_dot_cub(char *str, int *fd)
{
	if (ft_strlen(str) < 3 || ft_strcmp(&str[ft_strlen(str) - 4], ".cub"))
		return (ERROR);
	*fd = open(str, O_RDONLY);
	if (*fd == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_parsing(int argc, char **argv, t_data *data)
{
	char	**file;
	int		fd;

	if (argc != 2)
		return (ft_destroy_mlx(data), ft_error("Wrong number of args\n"), ERROR);
	if (ft_check_dot_cub(argv[1], &fd) != SUCCESS)
		return (ft_destroy_mlx(data), ft_error("Use a map.cub\n"), ERROR);
	if (ft_read_file(fd, &file) != SUCCESS)
	{
		close(fd);
		return (ft_destroy_mlx(data), ft_error("File error\n"), ERROR);
	}
	if (ft_get_texture(file, data) != SUCCESS)
	{
		close(fd);
		return (ft_destroy_mlx(data), free_2d(file), ERROR);
	}
	if (ft_get_map(file, data) != SUCCESS)
	{
		ft_destroy_img(data, 4);
		close(fd);
		return (ft_destroy_mlx(data), free_2d(file), ERROR);
	}
	close(fd);
	return (free_2d(file), SUCCESS);
}
