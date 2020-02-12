/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:42 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/27 17:51:43 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	calc_sidedist(t_var *v)
{
	if (v->raydir_x < 0)
	{
		v->step_x = -1;
		v->sidedist_x = (v->pos_x - v->map_x) * v->deltadist_x;
	}
	else
	{
		v->step_x = 1;
		v->sidedist_x = (v->map_x + 1.0 - v->pos_x) * v->deltadist_x;
	}
	if (v->raydir_y < 0)
	{
		v->step_y = -1;
		v->sidedist_y = (v->pos_y - v->map_y) * v->deltadist_y;
	}
	else
	{
		v->step_y = 1;
		v->sidedist_y = (v->map_y + 1.0 - v->pos_y) * v->deltadist_y;
	}
}

void	calc_hit(t_var *v)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (v->sidedist_x < v->sidedist_y)
		{
			v->sidedist_x += v->deltadist_x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->sidedist_y += v->deltadist_y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (v->map[v->map_x][v->map_y] > 0)
			hit = 1;
	}
}

void	calc_heightwall(t_var *v)
{
	if (v->side == 0)
		v->wall_dist = (v->map_x - v->pos_x + (1 - v->step_x) / 2) /
		v->raydir_x;
	else
		v->wall_dist = (v->map_y - v->pos_y + (1 - v->step_y) / 2) /
		v->raydir_y;
	v->line_height = (int)(HEIGHT / v->wall_dist);
	v->draw_start = -v->line_height / 2 + HEIGHT / 2;
	if (v->draw_start < 0)
		v->draw_start = 0;
	v->draw_end = v->line_height / 2 + HEIGHT / 2;
	if (v->draw_end >= HEIGHT)
		v->draw_end = HEIGHT - 1;
}

void	calc_colorwall(t_var *v)
{
	if (v->key.t_key == 1)
		v->text_num = 0;
	else
		v->color = RED;
	if ((v->step_x == 1) && ((v->step_y == -1) || v->step_y == 1))
	{
		if (v->key.t_key == 1)
			v->text_num = 1;
		else
			v->color = BLUE;
	}
	if (v->side == 1)
	{
		if (v->key.t_key == 1)
			v->text_num = 2;
		else
			v->color = YELLOW;
		if ((v->step_y == 1) && ((v->step_x == -1) || v->step_x == 1))
		{
			if (v->key.t_key == 1)
				v->text_num = 3;
			else
				v->color = GREEN;
		}
	}
}

void	*calc_ray_pos_dir(void *t)
{
	t_var *v;

	v = (t_var *)t;
	while (v->x < v->x_max)
	{
		v->camera_x = 2 * v->x / (double)WIDTH - 1;
		v->raydir_x = v->dir_x + v->plane_x * v->camera_x;
		v->raydir_y = v->dir_y + v->plane_y * v->camera_x;
		v->map_x = (int)v->pos_x;
		v->map_y = (int)v->pos_y;
		v->deltadist_x = fabs(1 / v->raydir_x);
		v->deltadist_y = fabs(1 / v->raydir_y);
		calc_sidedist(v);
		calc_hit(v);
		calc_heightwall(v);
		calc_colorwall(v);
		draw_y(v->x, v->draw_start, v->draw_end, v);
		v->x++;
	}
	return (0);
}
