/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:29 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/27 17:51:29 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	ratio(t_var *v)
{
	v->var.x1_m = v->var.x1 / (WIDTH / TAB_SIZE);
	v->var.y1_m = v->var.y1 / (WIDTH / TAB_SIZE);
	v->var.x2_m = v->var.x2 / (WIDTH / TAB_SIZE);
	v->var.y2_m = v->var.y2 / (WIDTH / TAB_SIZE);
	v->var.led = 0;
	line(v);
}

int		init_char_tab(t_var *v)
{
	int i;

	i = 0;
	if (!(v->var.tab = (char**)malloc(sizeof(char*) * TAB_SIZE + 1)))
		return (ft_error(v, "Malloc error"));
	while (i < TAB_SIZE)
	{
		if (!(v->var.tab[i] = (char*)malloc(sizeof(char) * TAB_SIZE + 1)))
			return (ft_error(v, "Malloc error"));
		v->var.tab[i] = ft_memset(v->var.tab[i], '0', TAB_SIZE);
		v->var.tab[i][TAB_SIZE] = '\0';
		i++;
	}
	v->var.tab[TAB_SIZE] = NULL;
	return (1);
}

void	init_var(t_var *v)
{
	v->var.x1 = 0;
	v->var.y1 = 0;
	v->var.y2 = 0;
	v->var.x2 = 0;
	v->var.i = 0;
}

int		map_builder_start(t_var *v)
{
	if (v->menu.menu_off == 0)
	{
		if (!(create_image_menu(v)))
			return (0);
		init_var(v);
		put_sides(v);
		v->var.p = 1;
		v->var.width = WIDTH_M;
		init_char_tab(v);
		mlx_hook(v->w.mlx_win, 4, 0, mouse_key, v);
	}
	else
	{
		mlx_destroy_image(v->w.mlx_ptr, v->var.win[1].mlx_img);
		if (!start(v))
			return (0);
	}
	return (1);
}
