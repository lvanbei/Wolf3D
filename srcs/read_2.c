/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:46:43 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/30 16:46:46 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		conversion_char_int(t_var *v, int fd, int ret)
{
	char *str;
	char **tab_char;

	while ((ret = get_next_line(fd, &str)) > 0)
	{
		v->read.i = -1;
		if (!(tab_char = ft_split_whitespace(str)))
			return (ft_error(v, "ft_split_whitespace error"));
		if (!(v->map[v->read.k] = (int*)malloc(sizeof(int)
		* len_line(tab_char, v))))
			return (ft_error(v, "Malloc error"));
		check_char_tab(tab_char, v->read.k, v);
		while (++v->read.i < v->columns)
			v->map[v->read.k][v->read.i] = ft_atoi(tab_char[v->read.i]);
		v->read.k++;
		free(str);
		free_tab(tab_char);
	}
	if (ret == -1)
		return (ft_error(v, "Get_next_line error"));
	if (close(fd) == -1)
		return (ft_error(v, "Close error"));
	return (1);
}

int		get_columns_conversion(t_var *v)
{
	int fd;
	int ret;

	ret = 0;
	v->read.k = 0;
	v->columns = 0;
	v->final_columns = 0;
	v->led = 0;
	if ((fd = open(v->read.map_name, O_RDONLY)) == -1)
		return (ft_error(v, "Open error"));
	if (!(v->map = (int**)malloc(sizeof(int*) * v->lines)))
		return (ft_error(v, "Malloc error"));
	return (conversion_char_int(v, fd, ret));
}
