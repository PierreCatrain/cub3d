/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:08:37 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/21 10:27:07 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_strlen(char *str)
{
    int index;

    index = 0;
    while (str[index])
        index++;
    return (index);
}

void ft_error(char *str)
{
    write(2, "ERROR\n", 6);
    write(2, str, ft_strlen(str));
}

int ft_strcmp(char *str1, char *str2)
{
    int index;

    index = 0;
    while (str1[index] && str2[index])
    {
        if (str1[index] != str2[index])
            break;
        index++;
    }
    return (str1[index] - str2[index]);
}

int ft_check_dot_cub(char *str, int *fd)
{
    if (ft_strlen(str) < 3 || ft_strcmp(&str[ft_strlen(str) - 4], ".cub"))
        return (ERROR);
    *fd = open(str, O_RDONLY);
    if (*fd == -1)
        return (ERROR);
    return (SUCCESS);
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

void	free_2d(char **str)
{
	int	index;

	if (str == NULL)
		return ;
	if (str[0] == NULL)
	{
		free(str);
		return ;
	}
	index = -1;
	while (str[++index])
		free(str[index]);
	free(str);
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

void	ft_printf_2d(char **str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		printf("%s\n", str[index]);
		index++;
	}
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

int ft_read_file(int fd, char ***file)
{
    char *new;
    char *read_str;
    int size;

    *file = malloc(sizeof(char *));
    if (*file == NULL)
        return (ERROR);
    (*file)[0] = NULL;
    new = malloc(sizeof(char));
    if (new == NULL)
        return (free(*file), ERROR);
    new[0] = '\0';
    read_str = malloc(2 * sizeof(char));
	if (read_str == NULL)
		return (free(*file), free(new), ERROR);
	read_str[0] = '\0';
    size = read(fd, read_str, 1);
    while (size > 0)
    {
        read_str[1] = '\0';
		if (read_str[0] == '\n')
		{
            new = ft_join_char(new, read_str[0]);
            if (new == NULL)
                return (free(read_str), ERROR);
            *file = ft_add_to_2d(*file, new);
            if (*file == NULL)
                return (free(read_str), free(new), ERROR);
            free(new);
            new = malloc(sizeof(char));
            if (new == NULL)
                return (free_2d(*file), free(read_str), ERROR);
            new[0] = '\0';
		}
        else
        {
            new = ft_join_char(new, read_str[0]);
            if (new == NULL)
                return (free(read_str), ERROR);
        }
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

int ft_is_line_empty(char *str)
{
    int index;

    index = -1;
    while (str[++index])
    {
        if (str[index] != ' ' && str[index] != '\t' && str[index] != '\n')
            return (0);
    }
    return (1);
}

int ft_get_six_first_line(char **file, char ***six_line)
{
    int index;
    int mini_index;
    int count;

    index = 0;
    mini_index = 0;
    count = 0;
    *six_line = malloc(sizeof(char *));
    if (*six_line == NULL)
        return (ERROR);
    (*six_line)[0] = NULL;
    while (file[index])
    {
        if (!ft_is_line_empty(file[index]))
        {
            *six_line = ft_add_to_2d(*six_line, file[index]);
            if (*six_line == NULL)
                return (ERROR);
            count++;
        }
        if (count == 6)
            break ;
        index++;
    }
    if (count != 6)
        return (free_2d(*six_line), ERROR);
    return (SUCCESS);
}

void free_mega_split(char **split[6], int index)
{
    while (--index >= 0)
        free_2d(split[index]);
}

int ft_find_index_split(char **split[6], char *find)
{
    int index;

    index = -1;
    while(*split[++index])
    {
        if (!ft_strcmp(*split[index], find))
            return (index);
    }
    return (index);
}

void ft_swap(char **split[6], int index_1, int index_2)
{
    char **tmp;

    tmp = split[index_1];
    split[index_1] = split[index_2];
    split[index_2] = tmp;
}

int ft_sort_split(char **split[6])
{
    if (ft_strcmp(split[0][0], "NO")) 
        ft_swap(split, 0, ft_find_index_split(split, "NO"));
    if (ft_strcmp(split[1][0], "SO"))
        ft_swap(split, 1, ft_find_index_split(split, "SO"));
    if (ft_strcmp(split[2][0], "EA"))
        ft_swap(split, 2, ft_find_index_split(split, "EA"));
    if (ft_strcmp(split[3][0], "WE"))
        ft_swap(split, 3, ft_find_index_split(split, "WE"));
    if (ft_strcmp(split[4][0], "F"))
        ft_swap(split, 4, ft_find_index_split(split, "F"));
    if (ft_strcmp(split[5][0], "C"))
        ft_swap(split, 5, ft_find_index_split(split, "C"));
    return (SUCCESS);
}

int check_and_sort_split(char **split[6])
{
    int index;
    int tab[6];

    index = -1;
    while (++index < 6)
    {
        if (ft_strlen_2d(split[index]) != 2)
            return (ERROR);
        tab[index] = 0;
    }
    index = -1;
    while (++index < 6)
    {
        if (!ft_strcmp(split[index][0], "NO"))
            tab[NORTH] = 1;
        else if (!ft_strcmp(split[index][0], "SO"))
            tab[SOUTH] = 1;
        else if (!ft_strcmp(split[index][0], "EA"))
            tab[EAST] = 1;
        else if (!ft_strcmp(split[index][0], "WE"))
            tab[WEST] = 1;
        else if (!ft_strcmp(split[index][0], "F"))
            tab[FLOOR + 4] = 1;
        else if (!ft_strcmp(split[index][0], "C"))
            tab[CELLING + 4] = 1;
    }
    index = -1;
    while (++index < 6)
    {
        if (tab[index] == 0)
        {
            printf("index %d\n", index);
            return (ERROR);
        }
    }
    return (ft_sort_split(split));
}

void ft_free_while_create_xpm(t_data *data, char **split[6], int index)
{
    while (--index >= 0)
        free(data->img[index].img_ptr);
    free_mega_split(split, 6);
}

char	*ft_strjoin_hexa(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str2 == NULL)
		return (free(str1), NULL);
	join = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (join == NULL)
		return (free(str1), free(str2), NULL);
	i = -1;
	while (str1[++i])
		join[i] = str1[i];
	j = -1;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}

char *ft_convert_hexa(int nb)
{
	unsigned int	n;
	char			*res;
	int				len;
    char *str;

	str = "0123456789ABCDEF";
    if (nb == ERROR_ATOI_HEXA)
    {
        return (NULL);
    }
	n = nb;
    len = 2;
	res = malloc(3 * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
    if (nb < 16)
    {
        res[0] = '0';
    }
	while (n > 0)
	{
		res[--len] = str[n % 16];
		n /= 16;
    }
	return (res);
}

long	ft_atoi_hexa(char *str)
{
	long	resultat;
	int		i;

	i = 0;
	resultat = 0;
	if (str[i] == '-')
		return (ERROR_ATOI_HEXA);
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat *= 10;
		resultat += str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || resultat > 255)
		return (ERROR_ATOI_HEXA);
	return (resultat);
}

int ft_transfo_color(int *hexa, char *entry)
{
    char **RGB;
    int     index;
    int rgb_int[3];

    RGB = ft_split(entry, ",");
    if (RGB == NULL)
        return (ERROR);
    if (ft_strlen_2d(RGB) != 3)
        return (free_2d(RGB), ERROR);
    index = 0;
    while (index < 3)
    {
        rgb_int[index] = ft_atoi_hexa(RGB[index]);
        if (rgb_int[index] == ERROR_ATOI_HEXA)
            return (free_2d(RGB), ERROR);
        index++;
    }
    *hexa = (rgb_int[0] << 16) + (rgb_int[1] << 8) + rgb_int[2];
    return (free_2d(RGB), SUCCESS);
}

int ft_get_color(char **split[6], t_data *data)
{
    int index;

    index = 4;
    while (index <= 5)
    {
        if (ft_transfo_color(&data->color[index - 4], split[index][1]) != SUCCESS)
            return (ERROR);
        index++;
    }
    return (SUCCESS);
}

void    ft_free_all_img_except_null(t_img img[4])
{
    int index;

    index = -1;
    while (++index < 4)
    {
        if (img[index].img_ptr != NULL)
            free(img[index].img_ptr);
        if (img[index].addr != NULL)
            free(img[index].addr);
    }
}

void *ft_new_img(t_img *img, t_data *data)
{
    void *new;
    int index;
    float index_actual;
    int bits_per_pixel;
    int size_line;
    int endian;
    char *actual_addr;
    int x;
    int y;

    new = mlx_new_image(data->mlx_ptr, SIZE_IMG, SIZE_IMG);
    if (new == NULL)
        return (free(img->img_ptr), NULL);
    img->addr = mlx_get_data_addr(new, &img->bits_per_pixel, &img->size_line, &img->endian);
    if (img->addr == NULL)
        return (free(new), free(img->img_ptr), NULL);
    actual_addr = mlx_get_data_addr(img->img_ptr, &bits_per_pixel, &size_line, &endian);
    if (actual_addr == NULL)
        return (free(new), free(img->img_ptr), NULL);
    printf("str %s et len %d\n", img->addr, ft_strlen(img->addr));
    x = -1;
    while (++x < SIZE_IMG)
    {
        y = -1;
        while (++y < SIZE_IMG)
        {
            index = (y * img->size_line) + (x * (img->bits_per_pixel / 8));
            index_actual = (y * img->size_line * ((float)img->height / SIZE_IMG)) + (x * (img->bits_per_pixel / 8) * ((float)img->width / SIZE_IMG));
            printf("index %d | index actuel %f\n", index, index_actual);
            img->addr[index] = actual_addr[(int)index_actual];
            img->addr[index + 1] = actual_addr[(int)index_actual + 1];
            img->addr[index + 2] = actual_addr[(int)index_actual + 2];
        }
    }
    return (new);
}

int ft_redimension_img(t_img img[4], t_data *data)
{
    int index;

    index = -1;
    while (++index < 4)
    {
        img[index].img_ptr = ft_new_img(&img[index], data);
        if (img[index].img_ptr == NULL)
            return (ft_free_all_img_except_null(img), ERROR);
        img[index].height = SIZE_IMG;
        img[index].width = SIZE_IMG;        
    }
    return (SUCCESS);
}

int ft_get_texture(char **file, t_data *data)
{
    char **six_line;
    char **split[6];
    int index;

    if (ft_get_six_first_line(file, &six_line) != SUCCESS)
        return (ERROR);
    index = -1;
    while (++index < 6)
    {
        split[index] = ft_split(six_line[index], " \t\n");
        if (split[index] == NULL)
            return (free_2d(six_line), free_mega_split(split, index), ERROR);
    }
    free_2d(six_line);
    if (check_and_sort_split(split) != SUCCESS)
        return (free_mega_split(split, 6), ERROR);
    index = -1;
    while (++index < 4)
    {
        data->img[index].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, split[index][1], &data->img[index].width, &data->img[index].height);
        if (data->img[index].img_ptr == NULL)
            return (ft_free_while_create_xpm(data, split, index), ERROR);
        data->img[index].addr = NULL;
    }
    //test
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img[0].img_ptr, 0, 0);
    //fin test
    if (ft_redimension_img(data->img, data) != SUCCESS)
        return (free_mega_split(split, 6), ERROR);
    //test
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img[0].img_ptr, 25, 0);
    //fin test
    if (ft_get_color(split, data) != SUCCESS)
        return (ft_free_while_create_xpm(data, split, 4), ERROR);
    return (free_mega_split(split, 6), SUCCESS);
}

void ft_free_img(t_data *data)
{
    int index;

    index = 0;
    while (index < 4)
    {
        free(data->img[index].img_ptr);
        index++;
    }
}

int ft_get_after_six_line(char ***after_six, char **file)
{
    int index;
    int mini_index;
    int count;

    index = 0;
    mini_index = 0;
    count = 0;
    *after_six = malloc(sizeof(char *));
    if (*after_six == NULL)
        return (ERROR);
    (*after_six)[0] = NULL;
    while (file[index])
    {
        if (count >= 6)
        {
            *after_six = ft_add_to_2d(*after_six, file[index]);
            if (*after_six == NULL)
                return (ERROR);
        }
        if (file[index][0] != '\n')
            count++;
        index++;
    }
    return (SUCCESS);
}

char *ft_without_last_line_return(char *str)
{
    char *new_str;
    int index;
    
    index = 0;
    new_str = malloc(sizeof(char));
    if (new_str == NULL)
        return (NULL);
    new_str[0] = '\0';
    while (str[index])
    {
        if (index == 0 || str[index] != '\n')
        {
            new_str = ft_join_char(new_str, str[index]);
            if (new_str == NULL)
                return (NULL);
        }
        index++;
    }
    return (new_str);
    
}

int ft_get_map_without_start_end(char ***map, char **after_six)
{
    int index_start;
    int index_end;

    index_start = 0;
    index_end = ft_strlen_2d(after_six) -1;
    while (after_six[index_start] && after_six[index_start][0] == '\n')
        index_start++;
    while (index_end > 0 && after_six[index_end][0] == '\n')
        index_end--;
    if (index_end <= index_start)
        return (ERROR);
    *map = malloc(sizeof(char *));
    if (*map == NULL)
        return (ERROR);
    (*map)[0] = NULL;
    while (after_six[index_start] && index_start <= index_end)
    {
        *map = ft_add_to_2d(*map, ft_without_last_line_return(after_six[index_start]));
        if (*map == NULL)
            return (ERROR);
        index_start++;
    }
    return (SUCCESS);
}

int ft_get_after_six_line_without_start_end(char ***map, char **file)
{
    char **after_six;

    if (ft_get_after_six_line(&after_six, file) != SUCCESS)
        return (ERROR);
    if (ft_get_map_without_start_end(map, after_six) != SUCCESS)
        return (free_2d(after_six), ERROR);
    return (free_2d(after_six), SUCCESS);
}

int ft_condition_no_line_empty(char **map)
{
    int index;

    index = 0;
    while (map[index])
    {
        if (map[index][0] == '\n')
            return (ERROR);
        index++;
    }
    return (SUCCESS);
}

int ft_condtion_no_unknown_character(char **map, char *charset)
{
    int index;
    int mini_index;
    
    index = -1;
    while (map[++index])
    {
        mini_index = -1;
        while(map[index][++mini_index])
        {
            if (ft_occ(charset, map[index][mini_index]) == 0)
                return (ERROR);
        }
    }
    return (SUCCESS);
}

int ft_only_one_player(char **map)
{
    int index;
    int index_mini;
    int count;

    count = 0;
    index = -1;
    while (map[++index])
    {
        index_mini = -1;
        while (map[index][++index_mini])
        {
            if (ft_occ("NSEW", map[index][index_mini]) != 0)
                count++;
        }
    }
    if (count != 1)
        return (ERROR);
    return (SUCCESS);
}

void ft_get_start_data(t_data *data)
{
    int index;
    int index_mini;

    index = -1;
    while (data->map[++index])
    {
        index_mini = -1;
        while (data->map[index][++index_mini])
        {
            if (ft_occ("NSEW", data->map[index][index_mini]) != 0)
            {
                data->start.direction = data->map[index][index_mini];
                data->start.x = index;
                data->start.y = index_mini;
                return ;
            }
        }
    }
}

int ft_get_max_x(char **map)
{
    int max_x;

    max_x = 0;
    while (map[max_x])
        max_x++;
    return (max_x);
}

int ft_get_max_y(char **map)
{
    int max_y;
    int len;
    int index;

    max_y = 0;
    index = -1;
    while (map[++index])
    {
        len = ft_strlen(map[index]);
        if (len > max_y)
            max_y = len;
    }
    return (max_y);
}

char *ft_complete_with_frame(char *str, int max_y)
{
    char *complete;
    int index;

    complete = malloc(sizeof(char));
    if (complete == NULL)
        return (NULL);
    complete[0] = '\0';
    complete = ft_join_char(complete, '.');
    if (complete == NULL)
        return (NULL);
    index = -1;
    while (str[++index])
    {
        complete = ft_join_char(complete, str[index]);
        if (complete == NULL)
            return (NULL);
    }
    while (++index <= max_y)
    {
        complete = ft_join_char(complete, '.');
        if (complete == NULL)
            return (NULL);
    }
    return (complete);
    
}

int ft_cpy_with_frame(char **map, char ***cpy)
{
    int max_x;
    int max_y;
    int x;

    max_x = ft_get_max_x(map) + 1;
    max_y = ft_get_max_y(map) + 1;
    *cpy = malloc(sizeof(char));
    if (*cpy == NULL)
        return (ERROR);
    (*cpy)[0] = NULL;
    x = 0;
    while (x <= max_x)
    {
        if (x == 0 || x == max_x)
        {
            *cpy = ft_add_to_2d(*cpy, ft_complete_with_frame("", max_y));
            if (*cpy == NULL)
                return (ERROR);
        }
        else
        {
            *cpy = ft_add_to_2d(*cpy, ft_complete_with_frame(map[x - 1], max_y));
            if (*cpy == NULL)
                return (ERROR);
        }
        x++;
    }
    return (SUCCESS);
}

int ft_already_add(t_coord *coord, int x, int y)
{
    while (coord != NULL)
    {
        if (coord->x == x && coord->y == y)
            return (1);
        if (coord->next == NULL)
            break;
        coord = coord->next;
    }
    return (0);
}

int ft_is_outside(int x, int y, char **map)
{
    if (ft_occ(" .", map[x + 1][y]) == 1)
        return (ERROR);
    if (ft_occ(" .", map[x - 1][y]) == 1)
        return (ERROR);
    if (ft_occ(" .", map[x][y + 1]) == 1)
        return (ERROR);
    if (ft_occ(" .", map[x][y - 1]) == 1)
        return (ERROR);
    return (SUCCESS);
}

int ft_get_coord(t_coord **coord, int x, int y, char **map)
{
    if (ft_occ(" .1", map[x + 1][y]) == 0 && ft_already_add(*coord, x + 1, y) == 0)
    {
        if (ft_add_back_coord(coord, ft_new_coord(x + 1, y)) != SUCCESS)
            return (ERROR);
        if (ft_get_coord(coord, x + 1, y, map) != SUCCESS)
            return (ERROR);
    }
    if (ft_occ(" .1", map[x - 1][y]) == 0 && ft_already_add(*coord, x - 1, y) == 0)
    {
        if (ft_add_back_coord(coord, ft_new_coord(x - 1, y)) != SUCCESS)
            return (ERROR);
        if (ft_get_coord(coord, x - 1, y, map) != SUCCESS)
            return (ERROR);
    }
    if (ft_occ(" .1", map[x][y + 1]) == 0 && ft_already_add(*coord, x, y + 1) == 0)
    {
        if (ft_add_back_coord(coord, ft_new_coord(x, y + 1)) != SUCCESS)
            return (ERROR);
        if (ft_get_coord(coord, x, y + 1, map) != SUCCESS)
            return (ERROR);
    }
    if (ft_occ(" .1", map[x][y - 1]) == 0 && ft_already_add(*coord, x, y - 1) == 0)
    {
        if (ft_add_back_coord(coord, ft_new_coord(x, y - 1)) != SUCCESS)
            return (ERROR);
        if (ft_get_coord(coord, x, y - 1, map) != SUCCESS)
            return (ERROR);
    }
    return (ft_is_outside(x, y, map));
}

int ft_nb_case(char **map)
{
    int count;
    int index;
    int mini_index;

    index = -1;
    count = 0;
    while (map[++index])
    {
        mini_index = -1;
        while (map[index][++mini_index])
        {
            if (ft_occ("NSEO0", map[index][mini_index]))
                count++;
        }
    }
    return (count);
}

int ft_is_close_and_one_block(t_data *data, char **cpy)
{
    t_coord *coord;
    int len;

    coord = NULL;
    if (ft_add_back_coord(&coord, ft_new_coord(data->start.x + 1, data->start.y + 1)) != SUCCESS)
        return (ERROR);
    if (ft_get_coord(&coord, data->start.x + 1, data->start.y + 1, cpy) != SUCCESS)
        return (ft_free_coord(coord), ERROR);
    len = 0;
    while (coord != NULL)
    {
        len++;
        if (coord->next == NULL)
            break;
        coord = coord->next;
    }
    if (len != ft_nb_case(data->map))
        return (ft_free_coord(coord), ERROR);
    return (ft_free_coord(coord), SUCCESS);
}

int ft_check_border(t_data *data)
{
    char **cpy;

    if (ft_cpy_with_frame(data->map, &cpy) != SUCCESS)
        return (ERROR);
    ft_printf_2d(cpy);
    if (ft_is_close_and_one_block(data, cpy) != SUCCESS)
        return (free_2d(cpy), ERROR);
    return (free_2d(cpy), SUCCESS);
}

int ft_get_map(char **file, t_data *data)
{
    if (ft_get_after_six_line_without_start_end(&data->map, file) != SUCCESS)
        return (ERROR);
    if (ft_condition_no_line_empty(data->map) != SUCCESS)
        return (free_2d(data->map), ERROR);
    if (ft_condtion_no_unknown_character(data->map, "10NSEW ") != SUCCESS)
        return (free_2d(data->map), ERROR);
    if (ft_only_one_player(data->map) != SUCCESS)
        return (free_2d(data->map), ERROR);
    ft_get_start_data(data);
    if (ft_check_border(data) != SUCCESS)
        return (free_2d(data->map), ERROR);
    return (SUCCESS);
}

int ft_parsing(int argc, char **argv, t_data *data)
{
    char **file;
    int fd;

    if (argc != 2)
        return (ft_error("Wrong number of args\n"), ERROR);
    if (ft_check_dot_cub(argv[1], &fd) != SUCCESS)
        return (ft_error("Use an available .cub\n"), ERROR);
    if (ft_read_file(fd, &file) != SUCCESS)
    {
        close(fd);
        return (ft_error("Error while reading the file\n"), ERROR);
    }
    if (ft_get_texture(file, data) != SUCCESS)
    {
        close(fd);
        free_2d(file);
        return (ft_error("Error with texture\n"), ERROR);
    }
    if (ft_get_map(file, data) != SUCCESS)
    {
        close(fd);
        free_2d(file);
        ft_free_img(data);
        return (ft_error("Error with map\n"), ERROR);
    }
    close(fd);
    free_2d(file);
    return (SUCCESS);
}