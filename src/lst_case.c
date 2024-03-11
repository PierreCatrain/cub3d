/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:38:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 00:44:40 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_coord *ft_new_coord(int x, int y)
{
    t_coord *new;
    
    new = malloc(sizeof(t_coord));
    if (new == NULL)
        return (NULL);
    new->prev = NULL;
    new->next = NULL;
    new->x = x;
    new->y = y;
    return (new);
}

t_coord  *ft_last_coord(t_coord *coord)
{
    while (coord->next != NULL)
        coord = coord->next;
    return (coord);
}

int ft_add_back_coord(t_coord **coord, t_coord *new)
{
    if (new == NULL)
        return (ERROR);
    if (*coord == NULL)
    {
        *coord = new;
    }
    else
    {
        new->prev = ft_last_coord(*coord);
        ft_last_coord(*coord)->next = new;
    }
    return (SUCCESS);
}

void ft_free_coord(t_coord *coord)
{
    t_coord *tmp;
    
    while (coord->prev != NULL)
        coord = coord->prev;
    while (coord != NULL)
    {
        tmp = coord;
        if (coord->next == NULL)
        {
            free(tmp);
            break ;
        }
        coord = coord->next;
        free(tmp);
    }
}
