/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:17:24 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/14 12:17:26 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		check_start_pos(t_var *v)
{
	int	x;
	int	y;

	x = 0;
	while (x < v->lines)
	{
		y = 0;
		while (y < v->final_columns)
		{
			if (v->map[x][y] == 0)
				return (1);
			y++;
		}
		x++;
	}
	return (ft_error(v, "map full of walls"));
}

void	var_init(t_var *v)
{
	v->pos_x = 1;
	v->pos_y = 1;
	while (v->map[(int)v->pos_x][(int)v->pos_y] != 0)
	{
		v->pos_x++;
		if (v->pos_x >= v->lines)
		{
			v->pos_y++;
			v->pos_x = 1;
		}
	}
	v->pos_x += 0.2;
	v->pos_y += 0.2;
	v->dir_x = 0.049184;
	v->dir_y = 0.998790;
	v->plane_x = 0.649213;
	v->plane_y = -0.031969;
	v->move_spd = SPEED;
	v->rot_spd = 0.035;
	v->led = 0;
	v->key.t_key = 1;
	v->text_num = -1;
	v->key.h_key = 1;
	v->i = 0;
}

int		multitrading(t_var *v)
{
	t_var	t[TREAD_NUMBER];
	int		i;

	i = -1;
	while (++i < TREAD_NUMBER)
	{
		ft_memcpy(&t[i], v, sizeof(t_var));
		t[i].x = i * WIDTH / TREAD_NUMBER;
		t[i].x_max = (i + 1) * WIDTH / TREAD_NUMBER;
		if (pthread_create(&(v->p_thread[i]), NULL, calc_ray_pos_dir, &t[i]))
			exit(1);
	}
	while (i--)
		pthread_join((v->p_thread[i]), NULL);
	if (!(mlx_put_image_to_window(v->w.mlx_ptr,
	v->w.mlx_win, v->w.mlx_img, 0, 0)))
		return (ft_error(v, "Put image error"));
	if (v->key.h_key % 2 == 1)
		str_menu(v);
	if (v->key.t_key >= 2)
		v->key.t_key = 0;
	return (1);
}

int		start(t_var *v)
{
	if (!(get_lines(v)))
		return (0);
	if (!(get_columns_conversion(v)))
		return (0);
	if (!(check_start_pos(v)))
		return (0);
	print_tab(v->map, v);
	var_init(v);
	if (!(load_textures(v)))
		return (0);
	system("afplay ./music/got.mp3 &");
	if (!(v->w.mlx_img = mlx_new_image(v->w.mlx_ptr, WIDTH, HEIGHT)))
		return (0);
	if (!(v->w.my_image_string = mlx_get_data_addr(v->w.mlx_img,
	&(v->w.bpp), &(v->w.s_l), &(v->w.endian))))
		return (0);
	mlx_loop_hook(v->w.mlx_ptr, move, v);
	return (1);
}

int		main(int argc, char **argv)
{
	t_var	v;

	if (argc != 2)
		ft_error(&v, "Usage error : ./wolf3d [map_builder] || [map path]");
	if (!(create_window(&v)))
		return (ft_error(&v, "Windows error"));
	if (!(ft_strcmp(argv[1], "map_builder")))
	{
		v.menu.menu_off = 0;
		v.read.map_name = "./maps/map0.txt";
		map_builder_start(&v);
	}
	else
	{
		v.menu.menu_off = 1;
		v.read.map_name = argv[1];
		if (!start(&v))
			return (0);
	}
	mlx_hook(v.w.mlx_win, DESTROY_NOTIFY, NO_EVENT_MASK, ft_close, &v);
	mlx_hook(v.w.mlx_win, 2, 0, key_press, &v);
	mlx_hook(v.w.mlx_win, 3, 0, key_release, &v);
	mlx_hook(v.w.mlx_win, 4, 0, mouse_key, &v);
	mlx_loop(v.w.mlx_ptr);
	return (0);
}
