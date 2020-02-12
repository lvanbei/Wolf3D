/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:33 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/27 17:51:33 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	dx_supp_dy(t_var *v)
{
	double	a;
	int		x;

	x = -1;
	if (v->var.dx >= v->var.dy && v->var.dx != 0 && v->var.dy != 0)
	{
		if (v->var.xstart > v->var.xend)
		{
			ft_swap(&v->var.xstart, &v->var.xend);
			ft_swap(&v->var.ystart, &v->var.yend);
		}
		a = ((float)(v->var.yend - v->var.ystart) /
		(v->var.xend - v->var.xstart));
		if (v->var.led == 1)
		{
			while (++x <= v->var.dx)
				fill_pixel_2(v, x + v->var.xstart,
				v->var.ystart + (x * a), 0xFF0000);
		}
		else
			while (++x <= v->var.dx)
				v->var.tab[(int)(v->var.ystart + (x * a))][(int)x
				+ v->var.xstart] = '1';
	}
}

void	dx_inf_dy(t_var *v)
{
	double	a;
	int		y;

	y = -1;
	if (v->var.dx < v->var.dy && v->var.dx != 0 && v->var.dy != 0)
	{
		if (v->var.ystart > v->var.yend)
		{
			ft_swap(&v->var.xstart, &v->var.xend);
			ft_swap(&v->var.ystart, &v->var.yend);
		}
		a = ((float)(v->var.xend - v->var.xstart) /
		(v->var.yend - v->var.ystart));
		if (v->var.led == 1)
		{
			while (++y <= v->var.dy)
				fill_pixel_2(v, v->var.xstart + (y * a),
				y + v->var.ystart, 0xFF0000);
		}
		else
			while (++y <= v->var.dy)
				v->var.tab[(int)(y + v->var.ystart)][(int)(v->var.xstart
				+ (y * a))] = '1';
	}
}

void	dx_null(t_var *v)
{
	int	y;

	if (v->var.dx == 0)
	{
		if (v->var.ystart > v->var.yend)
			ft_swap(&v->var.ystart, &v->var.yend);
		y = v->var.ystart - 1;
		if (v->var.led == 1)
		{
			while (++y <= v->var.yend)
				fill_pixel_2(v, v->var.xstart, y, 0xFF0000);
		}
		else
		{
			while (++y <= v->var.yend)
				v->var.tab[(int)y][(int)v->var.xstart] = '1';
		}
	}
}

void	dy_null(t_var *v)
{
	int x;

	x = 0;
	if (v->var.dy == 0)
	{
		if (v->var.xstart > v->var.xend)
			ft_swap(&v->var.xstart, &v->var.xend);
		x = v->var.xstart - 1;
		if (v->var.led == 1)
		{
			while (++x <= v->var.xend)
				fill_pixel_2(v, x, v->var.ystart, 0xFF0000);
		}
		else
		{
			while (++x <= v->var.xend)
				v->var.tab[(int)v->var.ystart][(int)x] = '1';
		}
	}
}

void	line(t_var *v)
{
	v->var.dx = abs(v->var.x2_m - v->var.x1_m);
	v->var.dy = abs(v->var.y2_m - v->var.y1_m);
	v->var.xstart = v->var.x1_m;
	v->var.xend = v->var.x2_m;
	v->var.ystart = v->var.y1_m;
	v->var.yend = v->var.y2_m;
	if (v->var.led == 1)
	{
		v->var.dx = abs(v->var.x2 - v->var.x1);
		v->var.dy = abs(v->var.y2 - v->var.y1);
		v->var.xstart = v->var.x1;
		v->var.xend = v->var.x2;
		v->var.ystart = v->var.y1;
		v->var.yend = v->var.y2;
	}
	dx_supp_dy(v);
	dx_inf_dy(v);
	dx_null(v);
	dy_null(v);
	if (v->var.led == 1)
		if (!(mlx_put_image_to_window(v->w.mlx_ptr, v->w.mlx_win,
		v->var.win[1].mlx_img, 50, 25)))
			ft_error(v, "Put image error");
}
