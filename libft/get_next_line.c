/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:30:07 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/01/10 15:30:07 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		get_line(char **holder, char **line)
{
	char *tmp;

	if ((*holder)[0] == '\0')
		return (0);
	if (ft_strchr(*holder, '\n') != NULL)
	{
		*(ft_strchr(*holder, '\n')) = '\0';
		*line = ft_strdup(*holder);
		tmp = ft_strdup(ft_strchr(*holder, '\0') + 1);
		free(*holder);
		if (tmp)
		{
			*holder = ft_strdup(tmp);
			free(tmp);
		}
	}
	else
	{
		*line = ft_strdup(*holder);
		ft_memdel((void **)holder);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int			br;
	char		buffer[BUFF_SIZE + 1];
	static char	*arr[OPEN_MAX];
	char		*tmp;

	if (fd == -1 || read(fd, buffer, 0) < 0 || !line)
		return (-1);
	if (!(arr[fd]))
		arr[fd] = ft_strnew(0);
	while (ft_strchr(arr[fd], '\n') == NULL)
	{
		br = read(fd, buffer, BUFF_SIZE);
		buffer[br] = '\0';
		if (br == 0)
			break ;
		tmp = ft_strjoin(arr[fd], buffer);
		free(arr[fd]);
		arr[fd] = ft_strdup(tmp);
		if (!(arr[fd]))
			arr[fd] = ft_strnew(0);
		free(tmp);
	}
	return (get_line(&arr[fd], line));
}
