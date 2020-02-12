/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:16:32 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/24 16:46:29 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		key_press(int key, t_var *v)
{
	if (v->menu.menu_off == 1)
	{
		if (key == ESC_KEY)
			ft_error(v, "Ciao !");
		if (key == W_KEY || key == UP_KEY)
			v->key.move_up = 1;
		if (key == DOWN_KEY || key == S_KEY)
			v->key.move_down = 1;
		if (key == D_KEY || key == RIGHT_KEY)
			v->key.move_right = 1;
		if (key == LEFT_KEY || key == A_KEY)
			v->key.move_left = 1;
		if (key == RTN_KEY)
			v->key.enter_key = 1;
		if (key == RSFT_KEY || key == LSFT_KEY)
			v->key.speed_key = 1;
		if (key == LCMD_KEY)
			v->key.command_key = 1;
		if (key == T_KEY)
			v->key.t_key++;
		if (key == H_KEY)
			v->key.h_key++;
	}
	return (map_builder_key_press(key, v));
}

int		key_release(int key, t_var *v)
{
	if (v->menu.menu_off == 1)
	{
		if (key == W_KEY || key == UP_KEY)
			v->key.move_up = 0;
		if (key == DOWN_KEY || key == S_KEY)
			v->key.move_down = 0;
		if (key == D_KEY || key == RIGHT_KEY)
			v->key.move_right = 0;
		if (key == LEFT_KEY || key == A_KEY)
			v->key.move_left = 0;
		if (key == RTN_KEY)
			v->key.enter_key = 0;
		if (key == RSFT_KEY || key == LSFT_KEY)
			v->key.speed_key = 0;
		if (key == LCMD_KEY)
			v->key.command_key = 0;
	}
	return (0);
}

void	side_move(t_var *v)
{
	double olddir_x;
	double oldplane_x;

	if (v->key.move_right == 1)
	{
		olddir_x = v->dir_x;
		v->dir_x = v->dir_x * cos(-v->rot_spd) - v->dir_y * sin(-v->rot_spd);
		v->dir_y = olddir_x * sin(-v->rot_spd) + v->dir_y * cos(-v->rot_spd);
		oldplane_x = v->plane_x;
		v->plane_x = v->plane_x * cos(-v->rot_spd) - v->plane_y *
		sin(-v->rot_spd);
		v->plane_y = oldplane_x * sin(-v->rot_spd) + v->plane_y *
		cos(-v->rot_spd);
	}
	if (v->key.move_left == 1)
	{
		olddir_x = v->dir_x;
		v->dir_x = v->dir_x * cos(v->rot_spd) - v->dir_y * sin(v->rot_spd);
		v->dir_y = olddir_x * sin(v->rot_spd) + v->dir_y * cos(v->rot_spd);
		oldplane_x = v->plane_x;
		v->plane_x = v->plane_x * cos(v->rot_spd) -
		v->plane_y * sin(v->rot_spd);
		v->plane_y = oldplane_x * sin(v->rot_spd) +
		v->plane_y * cos(v->rot_spd);
	}
}

void	back_front_move(t_var *v)
{
	v->si_x = 0.19;
	v->si_y = 0.19;
	if (v->dir_x < 0)
		v->si_x = -0.19;
	if (v->dir_y < 0)
		v->si_y = -0.19;
	if (v->key.move_up == 1)
	{
		if (!v->map[(int)(v->pos_x + v->dir_x *
		v->move_spd + v->si_x)][(int)v->pos_y])
			v->pos_x += v->dir_x * v->move_spd;
		if (!v->map[(int)v->pos_x][(int)(v->pos_y + v->dir_y *
		v->move_spd + v->si_y)])
			v->pos_y += v->dir_y * v->move_spd;
	}
	if (v->key.move_down == 1)
	{
		if (!v->map[(int)(v->pos_x - v->dir_x *
		v->move_spd - v->si_x)][(int)v->pos_y])
			v->pos_x -= v->dir_x * v->move_spd;
		if (!v->map[(int)v->pos_x][(int)(v->pos_y - v->dir_y *
		v->move_spd - v->si_y)])
			v->pos_y -= v->dir_y * v->move_spd;
	}
}

int		move(t_var *v)
{
	if (v->key.speed_key == 1)
	{
		v->move_spd = 0.17;
		v->rot_spd = 0.055;
	}
	if (v->key.speed_key == 0)
	{
		v->move_spd = SPEED;
		v->rot_spd = 0.035;
	}
	side_move(v);
	back_front_move(v);
	if (v->key.enter_key == 1)
		var_init(v);
	if (!(multitrading(v)))
		return (ft_error(v, "Multitrading error\n"));
	return (1);
}
