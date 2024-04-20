/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:38:27 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/20 20:22:33 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 600
# define ERROR_ATOI_HEXA -1
# define SIZE_IMG 50

enum error
{
    SUCCESS = 0,
    ERROR,
    ERROR_PARSING,
};

enum img
{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
};

enum color
{
    FLOOR = 0,
    CELLING,
};

typedef struct s_coord
{
    struct s_coord *prev;
    struct s_coord *next;
    int x;
    int y;
} t_coord;

typedef struct s_img
{
	void	*img_ptr;
    char    *addr;
	int		width;
	int		height;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
}	t_img;

typedef struct s_data
{
    t_img       img[4];
    int         color[2];
    int   RGB[2][3];
    char        **map;
    void        *mlx_ptr;
    void        *win_ptr;
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;
    t_img       screen;
    int         w;
    int         a;
    int         s;
    int         d;
    int         l;
    int         r;
} t_data;

typedef struct s_ray
{
    int w;
    int x;
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
    int h;
    int lineHeight;
    int drawStart;
    int drawEnd;
    double wallX;
    int texX;
    int texture;
    double step;
    int texY;
    double tmp;
} t_ray;

int ft_parsing(int argc, char **argv, t_data *data);
char	**ft_split(char *str, char *charset);
void	free_2d(char **str);
int ft_occ(char *str, char c);
t_coord *ft_new_coord(int x, int y);
t_coord  *ft_last_coord(t_coord *coord);
int ft_add_back_coord(t_coord **coord, t_coord *new);
void ft_free_coord(t_coord *coord);
void	ft_printf_2d(char **str);
int ft_raycast(t_data *data);
int ft_strlen(char *str);

#endif

// // void    ft_put_my_pixel(t_data *data, int x, int y, int color)
// // {
    
// // }

// void ft_drawline(int x, int drawStart, int drawEnd, int color, t_data *data)
// {
//     // drawEnd = drawStart + 2;
//     while (drawStart < drawEnd)
//     {
//         // ft_put_my_pixel(data, x, drawStart, color);
//         mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart, color);
//         drawStart++;
//         // printf("ici\n");
//     }
//     // mlx_pixel_put(data.mlx_ptr, data.win_ptr, x, drawStart, color);
//     // (void)drawEnd;
// }