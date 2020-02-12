/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:30:33 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/28 14:30:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	fill_pixel(t_var *v, int x, int y, int color)
{
	char	r;
	char	g;
	char	b;
	int		len;

	len = 4 * ((WIDTH) * y + x);
	r = (int)((color & 16711680) >> 16);
	g = (int)((color & 65280) >> 8);
	b = (int)(color & 255);
	v->w.my_image_string[len] = b;
	v->w.my_image_string[len + 1] = g;
	v->w.my_image_string[len + 2] = r;
}

int		ft_error(t_var *v, char *str_error)
{
	ft_putendl(str_error);
	if (v->map)
		free_tab_int(v->map, v->read.k);
	if (v->var.str)
		free(v->var.str);
	if (v->var.tab)
		free_tab(v->var.tab);
	if (v->w.mlx_win)
		mlx_clear_window(v->w.mlx_ptr, v->w.mlx_win);
	system("killall afplay 2&>/dev/null >/dev/null");
	exit(1);
	return (-1);
}

int		ft_close(t_var *v)
{
	ft_putendl("Ciao !");
	if (v->map)
		free_tab_int(v->map, v->read.k);
	if (v->var.str)
		free(v->var.str);
	if (v->var.tab)
		free(v->var.tab);
	if (v->w.mlx_win)
		mlx_clear_window(v->w.mlx_ptr, v->w.mlx_win);
	system("killall afplay 2&>/dev/null >/dev/null");
	exit(1);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_tab_int(int **tab, int len)
{
	int i;

	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
	tab = NULL;
}
