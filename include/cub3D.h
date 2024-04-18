/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:38:27 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/18 15:33:52 by lgarfi           ###   ########.fr       */
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

# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500
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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

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

typedef struct s_start
{
    char direction;
    double x;
    double y;
} t_start;

typedef struct s_data
{
    t_img       img[4];
    int         color[2];
    char        **map;
    t_start     start;
    void        *mlx_ptr;
    void        *win_ptr;
	t_vars		vars;
} t_data;

typedef struct s_ray
{
	double	posX;
	double	posY;
	double	raydirX;
	double	raydirY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	deltaDistX;
	double	deltaDistY;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	int		hit;
	int		side;
	double	perpwallDist;
	int		lineHeight;
	int		h;
	int		drawStart;
	int		drawEnd;
}	t_ray;

int ft_parsing(int argc, char **argv, t_data *data);
char	**ft_split(char *str, char *charset);
void	free_2d(char **str);
int ft_occ(char *str, char c);
t_coord *ft_new_coord(int x, int y);
t_coord  *ft_last_coord(t_coord *coord);
int ft_add_back_coord(t_coord **coord, t_coord *new);
void ft_free_coord(t_coord *coord);

#endif