/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:20:48 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/18 19:35:07 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_split(char **split, int j)
{
	j--;
	while (j >= 0)
		free(split[j--]);
	free(split);
}

int ft_occ(char *str, char c)
{
	int index;
	int count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}

int	ft_mega_malloc(char *str, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\0' && ft_occ(charset, str[i]) == 0 && (str[i + 1] == '\0' \
					|| ft_occ(charset, str[i + 1]) == 0))
			count++;
		i++;
	}
	return (count);
}

int	ft_mini_malloc(char *str, char *charset, int i)
{
	int	count;

	count = 0;
	while (str[i] != '\0' && ft_occ(charset, str[i]) == 0)
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_remplissage_split(char *str, char *charset, int i)
{
	char	*mini_split;
	int		j;

	mini_split = malloc((ft_mini_malloc(str, charset, i) + 1) * sizeof(char));
	if (mini_split == NULL)
		return (NULL);
	j = 0;
	while (str[i + j] != '\0' && ft_occ(charset, str[i + j]) == 0)
	{
		mini_split[j] = str[i + j];
		j++;
	}
	mini_split[j] = '\0';
	return (mini_split);
}

char	**ft_split(char *str, char *charset)
{
	char	**split;
	int		i;
	int		j;
	int		new;

	split = malloc((ft_mega_malloc(str, charset) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = -1;
	j = -1;
	new = 1;
	while (str[++i])
	{
		if (new == 1 && ft_occ(charset, str[i]) == 0)
		{
			split[++j] = ft_remplissage_split(str, charset, i);
			if (split[j] == NULL)
				return (ft_free_split(split, j), NULL);
			new = 0;
		}
		else if (new == 0 && ft_occ(charset, str[i]) != 0 && ft_occ(charset, str[i + 1]) == 0 \
		&& str[i + 1] != '\0')
			new = 1;
	}
	split[++j] = NULL;
	return (split);
}
