/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/27 17:51:37 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	put_in_string(t_var *v)
{
	while (v->read.i < (TAB_SIZE * TAB_SIZE) * 2)
	{
		if (v->var.tab[v->read.j][v->read.k] == '\0')
		{
			v->read.k = 0;
			v->read.j++;
		}
		if (v->read.i % 2 == 1)
			v->read.i++;
		else
		{
			if (v->var.tab[v->read.j][v->read.k + 1] == '\0')
			{
				if (v->read.j == TAB_SIZE - 1)
					break ;
				v->var.str[v->read.i] = '\n';
			}
			else
				v->var.str[v->read.i] = v->var.tab[v->read.j][v->read.k];
			v->read.i++;
			v->read.k++;
		}
	}
}

int		make_tab_good(t_var *v)
{
	int len;

	v->read.i = -1;
	v->read.j = 1;
	len = (TAB_SIZE * TAB_SIZE) * 2 + 1;
	if (!(v->var.str = (char*)malloc(sizeof(char) *
	(TAB_SIZE * TAB_SIZE) * 2 + 1)))
		return (ft_error(v, "Malloc error"));
	while (++v->read.i < len)
	{
		if (v->read.i == TAB_SIZE * v->read.j)
		{
			v->var.str[v->read.i] = '\n';
			v->read.j++;
		}
		else
			v->var.str[v->read.i] = ' ';
	}
	v->var.str[v->read.i] = '\0';
	v->read.i = 0;
	v->read.j = 0;
	v->read.k = 0;
	put_in_string(v);
	return (1);
}

int		write_tab(t_var *v)
{
	int fd;

	if ((fd = open("./maps/map0.txt", O_WRONLY)) == -1)
		return (ft_error(v, "Open map builder error"));
	ft_putstr_fd(v->var.str, fd);
	free_tab(v->var.tab);
	v->var.tab = NULL;
	free(v->var.str);
	v->var.str = NULL;
	if (close(fd) == -1)
		return (ft_error(v, "Close map builder error"));
	return (1);
}
