/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:17:44 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/24 16:46:37 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	sky(t_var *v, int column, int y)
{
	int i;

	i = 0;
	while (i < y)
	{
		fill_pixel(v, column, i, 0x00B6FF);
		i++;
	}
}

void	ground(t_var *v, int column, int end)
{
	while (end < HEIGHT && end >= 0)
	{
		fill_pixel(v, column, end, 0xA7A7A7);
		end++;
	}
}

void	put_texture(t_var *v, int column, int y, int end)
{
	int		len;
	int		y_text;
	double	x_text;
	int		img_size;

	img_size = 720;
	if (v->side == 0)
		x_text = v->pos_y + v->wall_dist * v->raydir_y;
	else
		x_text = v->pos_x + v->wall_dist * v->raydir_x;
	x_text *= (double)(img_size);
	if (v->side == 0 && v->raydir_x > 0)
		x_text = fabs(img_size - x_text - 1);
	if (v->side == 1 && v->raydir_y < 0)
		x_text = fabs(img_size - x_text - 1);
	while (y < end)
	{
		len = 4 * ((WIDTH) * y + column);
		y_text = abs((((y * 256 - HEIGHT * 128 + v->line_height * 128)
		* img_size) / v->line_height) / 256);
		ft_memcpy(&v->w.my_image_string[len], &v->text[v->text_num].
		my_texture_string[y_text % img_size * v->text[v->text_num].s_l +
		(int)x_text % img_size * (v->text[v->text_num].bpp / 8)], sizeof(int));
		y++;
	}
}

void	draw_y(int column, int y, int end, t_var *v)
{
	sky(v, column, y);
	if (v->key.t_key == 1)
		put_texture(v, column, y, end);
	else
	{
		y--;
		while (++y < end)
			fill_pixel(v, column, y, v->color);
	}
	ground(v, column, end);
}
