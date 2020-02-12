/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:17:31 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/24 16:47:18 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		get_lines(t_var *v)
{
	char	*str;
	int		fd;
	int		ret;

	v->lines = 0;
	if ((fd = open(v->read.map_name, O_RDONLY)) == -1)
		return (ft_error(v, "Open error"));
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		v->lines++;
		free(str);
	}
	if (ret == -1)
		return (ft_error(v, "Get_next_line error"));
	if (close(fd) == -1)
		return (ft_error(v, "Close error"));
	return (1);
}

void	print_tab(int **tab, t_var *v)
{
	int	i;
	int	j;

	i = -1;
	while (++i < v->lines)
	{
		j = -1;
		while (++j < v->final_columns)
			ft_putnbr(tab[i][j]);
		ft_putchar('\n');
	}
}

int		len_line(char **tab, t_var *v)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (tab[result])
		result++;
	v->columns = result;
	return (result);
}

int		check_and_replace(t_var *v, int i, char **tab, int line)
{
	int j;

	j = 0;
	while (tab[i][j])
	{
		if (tab[i][j] < 48 || tab[i][j] > 57)
		{
			ft_putstr("Error tab case : [");
			ft_putnbr(i + 1);
			ft_putstr("] [");
			ft_putnbr(line + 1);
			return (ft_error(v, "]"));
		}
		else if (v->led == 0)
			tab[i][j] = '1';
		else if (line + 1 == v->lines)
			tab[i][j] = '1';
		if (i == 0)
			tab[0][j] = '1';
		if (i == v->columns - 1)
			tab[v->columns - 1][j] = '1';
		j++;
	}
	return (1);
}

int		check_char_tab(char **tab, int line, t_var *v)
{
	int i;

	i = -1;
	while (tab[++i])
		check_and_replace(v, i, tab, line);
	if (v->led == 0)
	{
		v->final_columns = i;
		v->led = 1;
	}
	if (i != v->final_columns)
		return (ft_error(v, "Not same columns len"));
	return (1);
}
