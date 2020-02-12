/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:15:35 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/28 15:50:18 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		mouse_key(int key, int x, int y, t_var *v)
{
	if (v->menu.menu_off == 0)
	{
		(void)key;
		if (x < 50 || x > WIDTH - 50)
		{
			v->var.x1 = 0;
			v->var.y1 = 0;
			return (0);
		}
		if (y < 25 || y > HEIGHT - 25)
		{
			v->var.x1 = 0;
			v->var.y1 = 0;
			return (0);
		}
		x -= 50;
		y -= 25;
		mouse_key_2(x, y, v);
	}
	return (0);
}

void	mouse_key_2(int x, int y, t_var *v)
{
	if (v->var.i == 0)
	{
		v->var.x1 = x;
		v->var.y1 = y;
		v->var.i++;
	}
	else
	{
		if (v->var.i > 1)
		{
			v->var.x1 = v->var.x2;
			v->var.y1 = v->var.y2;
		}
		v->var.x2 = x;
		v->var.y2 = y;
		v->var.i++;
	}
	if (v->var.x2 != 0 && v->var.y2 != 0)
	{
		v->var.led = 1;
		line(v);
		ratio(v);
	}
}

void	map_builder_key_press_2(int key, t_var *v)
{
	if (key == SP_KEY)
	{
		v->var.i = 0;
		v->var.x2 = 0;
		v->var.y2 = 0;
	}
	if (key == O_KEY)
	{
		if (!(make_tab_good(v)))
			exit(1);
		if (!(write_tab(v)))
			exit(1);
		v->menu.menu_off = 1;
		map_builder_start(v);
	}
}

void	clear_img(t_var *v)
{
	int x;
	int y;

	x = -1;
	v->var.p = 1;
	v->var.width = WIDTH_M;
	while (++x < WIDTH_M)
	{
		y = -1;
		while (++y < HEIGHT_M)
			fill_pixel_2(v, x, y, 0x000000);
	}
}

int		map_builder_key_press(int key, t_var *v)
{
	if (v->menu.menu_off == 0)
	{
		if (key == ESC_KEY)
			ft_error(v, "Ciao !");
		if (key == RTN_KEY)
		{
			clear_img(v);
			if (!(mlx_put_image_to_window(v->w.mlx_ptr, v->w.mlx_win,
							v->var.win[1].mlx_img, 50, 25)))
				ft_error(v, "Put image error");
			init_char_tab(v);
			v->var.i = 0;
			v->var.x1 = 0;
			v->var.x2 = 0;
		}
		map_builder_key_press_2(key, v);
	}
	return (0);
}
