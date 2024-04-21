/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:38:27 by picatrai          #+#    #+#             */
/*   Updated: 2024/04/21 20:09:31 by picatrai         ###   ########.fr       */
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

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 600
# define ERROR_ATOI_HEXA -1
# define SIZE_IMG 50

enum	e_error
{
	SUCCESS = 0,
	ERROR,
	ERROR_PARSING,
};

enum	e_img
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
};

enum	e_color
{
	FLOOR = 0,
	CELLING,
};

typedef struct s_coord
{
	struct s_coord	*prev;
	struct s_coord	*next;
	int				x;
	int				y;
}	t_coord;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_data
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	t_img	screen;
	t_img	img[4];
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		color[2];
	int		rgb[2][3];
	int		w;
	int		a;
	int		s;
	int		d;
	int		l;
	int		r;
}	t_data;

typedef struct s_ray
{
	double	raydir_y;
	double	camera_x;
	double	raydir_x;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	double	wall_x;
	double	step;
	double	tmp;
	int		w;
	int		x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		h;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		tex_x;
	int		texture;
	int		tex_y;
}	t_ray;

t_coord	*ft_last_coord(t_coord *coord);
t_coord	*ft_new_coord(int x, int y);

char	*ft_strdup(char *str);
char	**ft_add_to_2d(char **base, char *add);
char	*ft_join_char(char *str, char c);
char	**ft_split(char *str, char *charset);

void	free_2d(char **str);
void	ft_free_coord(t_coord *coord);
void	ft_key_manage(t_data *data);
void	ft_where_to_draw(t_ray *ray, t_data data);
void	ft_which_texture(t_ray *ray, t_data data);
void	ft_complete_screen(t_ray *ray, t_data *data);
void	ft_destroy_all_except_screen(t_data *data);
void	ft_destroy_all(t_data *data);
void	free_mega_split(char **split[6], int index);
void	ft_free_while_create_xpm(t_data *data, char **split[6], int index);
void	ft_error(char *str);
void	ft_free_all_img_except_null(t_img img[4]);
void	ft_get_start_data(t_data *data);
void	ft_destroy_img(t_data *data, int index);
void	ft_destroy_mlx(t_data *data);

long	ft_atoi_hexa(char *str);

int		ft_parsing(int argc, char **argv, t_data *data);
int		ft_occ(char *str, char c);
int		ft_add_back_coord(t_coord **coord, t_coord *new);
int		ft_raycast(t_data *data);
int		ft_strlen(char *str);
int		handle_keypress(int keysym, t_data *data);
int		handle_keyrelease(int keysym, t_data *data);
int		ft_handle_mouse(int x, int y, t_data *data);
int		ft_destroy_and_exit(t_data *data);
int		ft_strlen(char *str);
int		ft_strlen_2d(char **str);
int		ft_strcmp(char *str1, char *str2);
int		ft_occ(char *str, char c);
int		ft_read_file(int fd, char ***file);
int		ft_get_texture(char **file, t_data *data);
int		check_and_sort_split(char **split[6]);
int		ft_redimension_img(t_img img[4], t_data *data);
int		ft_get_color(char **split[6], t_data *data);
int		ft_get_map(char **file, t_data *data);
int		ft_condition_no_line_empty(char **map);
int		ft_check_border(t_data *data);
int		ft_is_close_and_one_block(t_data *data, char **cpy);
int		ft_only_one_player(char **map);
int		ft_condtion_no_unknown_character(char **map, char *charset);
int		ft_cpy_with_frame(char **map, char ***cpy, int max_x, int max_y);
int		ft_get_max_x(char **map);
int		ft_get_max_y(char **map);
int		ft_get_coord(t_coord **coord, int x, int y, char **map);
int		ft_nb_case(char **map);
int		ft_already_add(t_coord *coord, int x, int y);
#endif
