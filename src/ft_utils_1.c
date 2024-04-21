/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:32:29 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 04:30:12 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	ft_strlen_2d(char **str)
{
	int	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		index;

	new = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	index = -1;
	while (str[++index])
		new[index] = str[index];
	new[index] = '\0';
	return (new);
}

char	**ft_add_to_2d(char **base, char *add)
{
	char	**new;
	int		index;

	if (add == NULL)
	{
		return (free_2d(base), NULL);
	}
	new = malloc((ft_strlen_2d(base) + 2) * sizeof(char *));
	if (new == NULL)
		return (free_2d(base), NULL);
	index = 0;
	while (base != NULL && base[index])
	{
		new[index] = ft_strdup(base[index]);
		if (new[index] == NULL)
			return (free_2d(base), NULL);
		index++;
	}
	new[index] = ft_strdup(add);
	if (new[index] == NULL)
		return (NULL);
	new[++index] = NULL;
	if (base != NULL)
		free_2d(base);
	return (new);
}

char	*ft_join_char(char *str, char c)
{
	char	*join;
	int		i;

	join = malloc ((ft_strlen(str) + 2) * sizeof(char));
	if (join == NULL)
		return (free(str), NULL);
	i = -1;
	while (str[++i])
		join[i] = str[i];
	join[i++] = c;
	join[i] = '\0';
	return (free(str), join);
}
