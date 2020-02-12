/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:00:58 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/30 16:00:59 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	fill_pixel_2(t_var *v, int x, int y, int color)
{
	char	r;
	char	g;
	char	b;
	int		len;

	len = 4 * ((v->var.width) * y + x);
	r = (int)((color & 16711680) >> 16);
	g = (int)((color & 65280) >> 8);
	b = (int)(color & 255);
	v->var.win[v->var.p].my_image_string[len] = b;
	v->var.win[v->var.p].my_image_string[len + 1] = g;
	v->var.win[v->var.p].my_image_string[len + 2] = r;
}

int		str_menu(t_var *v)
{
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 180, 5, 0xFFFFFF, "MENU");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 180, 12, 0xFF0000, "----");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 180, -3, 0xFF0000, "----");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 22,
		0xFFFFFF, "W, S A, D or the arrows to move");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 39,
		0xFFFFFF, "SHIFT to run");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 54,
		0xFFFFFF, "T to put/hide textures");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 71,
		0xFFFFFF, "H to hide/put menu");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 88,
		0xFFFFFF, "ENTER to retry");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 105,
		0xFFFFFF, "ESC to quit");
	return (0);
}

void	top_and_floor_baners(t_var *v)
{
	int x;
	int y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y <= 25)
			fill_pixel_2(v, x, y, 0x0075FF);
	}
	x = -1;
	while (++x < WIDTH)
	{
		y = HEIGHT - ((HEIGHT - HEIGHT_M) / 2) - 1;
		while (++y < HEIGHT)
			fill_pixel_2(v, x, y, 0x0075FF);
	}
}

void	sides_baners(t_var *v)
{
	int x;
	int y;

	x = -1;
	while (++x < (WIDTH - WIDTH_M) / 2)
	{
		y = -1;
		while (++y < HEIGHT)
			fill_pixel_2(v, x, y, 0x0075FF);
	}
	x = WIDTH - ((WIDTH - WIDTH_M) / 2) - 1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			fill_pixel_2(v, x, y, 0x0075FF);
	}
}

void	put_sides(t_var *v)
{
	char	*str;
	char	*str2;

	v->var.p = 0;
	v->var.width = WIDTH;
	top_and_floor_baners(v);
	sides_baners(v);
	if (!(mlx_put_image_to_window(v->w.mlx_ptr, v->w.mlx_win,
	v->var.win[0].mlx_img, 0, 0)))
		ft_error(v, "put image error");
	mlx_destroy_image(v->w.mlx_ptr, v->var.win[0].mlx_img);
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, (WIDTH / 2) - 52, 3,
	0xFFFFFF, "MAP BUILDER");
	str = "DRAW W/ THE MOUSE | PRESS SPACE TO RESET START POINT | PRESS ENTER";
	str2 = "TO CLEAN THE SCREEN | PRESS \"O_KEY\" TO START THE GAME";
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 40, 696, 0xFFFFFF, str);
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 710, 696, 0xFFFFFF, str2);
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 3, 0xFFFFFF, "START HERE");
	mlx_string_put(v->w.mlx_ptr, v->w.mlx_win, 20, 25, 0xFFFFFF, "->");
}
