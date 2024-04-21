/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:45:44 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 04:41:04 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_set_read_file(char ***file, char **new, char **read_str)
{
	*file = malloc(sizeof(char *));
	if (*file == NULL)
		return (ERROR);
	(*file)[0] = NULL;
	*new = malloc(sizeof(char));
	if (*new == NULL)
		return (free(*file), ERROR);
	(*new)[0] = '\0';
	*read_str = malloc(2 * sizeof(char));
	if (*read_str == NULL)
		return (free(*file), free(new), ERROR);
	(*read_str)[0] = '\0';
	return (SUCCESS);
}

int	ft_read_file_core(char **read_str, char **new, char ***file)
{
	(*read_str)[1] = '\0';
	if ((*read_str)[0] == '\n')
	{
		*new = ft_join_char(*new, (*read_str)[0]);
		if (new == NULL)
			return (free(*read_str), ERROR);
		*file = ft_add_to_2d(*file, *new);
		if (*file == NULL)
			return (free(*read_str), free(*new), ERROR);
		free(*new);
		*new = malloc(sizeof(char));
		if (*new == NULL)
			return (free_2d(*file), free(*read_str), ERROR);
		(*new)[0] = '\0';
	}
	else
	{
		*new = ft_join_char(*new, (*read_str)[0]);
		if (*new == NULL)
			return (free(*read_str), ERROR);
	}
	return (SUCCESS);
}

int	ft_read_file(int fd, char ***file)
{
	char	*new;
	char	*read_str;
	int		size;

	if (ft_set_read_file(file, &new, &read_str) == ERROR)
		return (ERROR);
	size = read(fd, read_str, 1);
	while (size > 0)
	{
		if (ft_read_file_core(&read_str, &new, file) == ERROR)
			return (ERROR);
		size = read(fd, read_str, 1);
	}
	if (new[0] != '\0')
	{
		new = ft_join_char(new, read_str[0]);
		if (new == NULL)
			return (free(read_str), ERROR);
		*file = ft_add_to_2d(*file, new);
		if (*file == NULL)
			return (free(read_str), free(new), ERROR);
	}
	if (size == -1)
		return (free_2d(*file), free(new), free(read_str), ERROR);
	return (free(new), free(read_str), SUCCESS);
}
