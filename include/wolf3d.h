/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:18:31 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/14 12:18:32 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include "keycode.h"
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# define WIDTH 1280
# define HEIGHT 720
# define WIDTH_M 1180
# define HEIGHT_M 670
# define TAB_SIZE 50
# define TEXTWIDTH 128
# define TEXTHEIGHT 128
# define NO_EVENT_MASK 0L
# define DESTROY_NOTIFY 17
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define BUF_SIZE 24
# define SPEED 0.07
# define TREAD_NUMBER 16

typedef struct	s_win_m
{
	void		*mlx_img;
	char		*my_image_string;
	int			bpp;
	int			s_l;
	int			endian;
}				t_win_m;

typedef struct	s_var_m
{
	t_win_m		win[2];
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			i;
	char		**tab;
	char		*str;
	int			x1_m;
	int			y1_m;
	int			x2_m;
	int			y2_m;
	int			p;
	int			width;
	int			led;
	int			xstart;
	int			xend;
	int			ystart;
	int			yend;
	int			dx;
	int			dy;

}				t_var_m;

typedef struct	s_win
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_img;
	char		*my_image_string;
	int			bpp;
	int			s_l;
	int			endian;

}				t_win;

typedef struct	s_read
{
	int			fd;
	int			readed_bite;
	char		*map_name;
	char		*str;
	char		*tmp;
	int			i;
	int			j;
	int			k;
}				t_read;

typedef struct	s_key
{
	int			move_up;
	int			move_down;
	int			move_right;
	int			move_left;
	int			enter_key;
	int			speed_key;
	int			mouse_x1;
	int			mouse_y1;
	int			mouse_x2;
	int			mouse_y2;
	int			command_key;
	int			m_key;
	int			t_key;
	int			h_key;

}				t_key;

typedef	struct	s_menu
{
	int			menu_off;
}				t_menu;

typedef	struct	s_text
{
	void		*img;
	char		*my_texture_string;
	int			bpp;
	int			s_l;
	int			endian;
}				t_text;

typedef struct	s_var
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		raydir_y;
	double		raydir_x;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	double		move_spd;
	double		rot_spd;
	int			x;
	int			x_max;
	t_win		w;
	t_read		read;
	t_key		key;
	t_menu		menu;
	t_text		text[4];
	t_var_m		var;
	int			columns;
	int			final_columns;
	int			led;
	int			lines;
	pthread_t	p_thread[TREAD_NUMBER];
	int			width;
	int			**map;
	int			text_num;
	double		si_x;
	double		si_y;
	int			i;
}				t_var;

/*
** main.c
*/

int				check_start_pos(t_var *v);
int				start(t_var *v);
int				multitrading(t_var *v);
void			var_init(t_var *v);

/*
** create_images.c
*/

int				create_image_menu(t_var *v);
int				load_textures(t_var *v);
int				create_window(t_var *v);

/*
** hook.c
*/

int				key_press(int key, t_var *v);
int				key_release(int key, t_var *v);
int				move(t_var *v);

/*
** map_builder_hook.c
*/

int				mouse_key(int key, int x, int y, t_var *v);
void			mouse_key_2(int x, int y, t_var *v);
int				map_builder_key_press(int key, t_var *v);
void			map_builder_key_press_2(int key, t_var *v);
void			clear_img(t_var *v);

/*
** map_builder_lines.c
*/
void			line(t_var *v);

/*
** map_builder_read.c
*/

int				write_tab(t_var *v);
int				make_tab_good(t_var *v);
void			put_in_string(t_var *v);

/*
** map_builder.c
*/

int				map_builder_start(t_var *v);
void			init_var(t_var *v);
int				init_char_tab(t_var *v);
void			ratio(t_var *v);

/*
** menu.c
*/

void			fill_pixel_2(t_var *v, int x, int y, int color);
int				str_menu(t_var *v);
void			put_sides(t_var *v);

/*
** raycasting.c
*/

void			*calc_ray_pos_dir(void *t);

/*
** read.c
*/

int				check_char_tab(char **tab, int line, t_var *v);
int				check_and_replace(t_var *v, int i, char **tab, int line);
int				len_line(char **tab, t_var *v);
void			print_tab(int **tab, t_var *v);
int				get_lines(t_var *v);

/*
**read_2.c
*/

int				get_columns_conversion(t_var *v);
int				conversion_char_int(t_var *v, int fd, int ret);

/*
** textures.c
*/

void			draw_y(int column, int y, int end, t_var *v);
void			put_texture(t_var *v, int column, int y, int end);
void			ground(t_var *v, int column, int end);
void			sky(t_var *v, int column, int y);

/*
**tools.c
*/

void			free_tab_int(int **tab, int len);
void			free_tab(char **tab);
int				ft_close(t_var *v);
void			fill_pixel(t_var *v, int x, int y, int color);
int				ft_error(t_var *v, char *str_error);
#endif
