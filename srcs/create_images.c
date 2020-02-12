/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:21:06 by lvan-bei          #+#    #+#             */
/*   Updated: 2019/05/28 16:25:04 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int		create_image_menu(t_var *v)
{
	if (!(v->var.win[0].mlx_img = mlx_new_image(v->w.mlx_ptr, WIDTH, HEIGHT)))
		return (0);
	if (!(v->var.win[1].mlx_img = mlx_new_image(v->w.mlx_ptr,
	WIDTH_M, HEIGHT_M)))
		return (0);
	if (!(v->var.win[0].my_image_string = mlx_get_data_addr(
		v->var.win[0].mlx_img, &(v->var.win[0].bpp), &(v->var.win[0].s_l),
		&(v->var.win[0].endian))))
		return (0);
	if (!(v->var.win[1].my_image_string = mlx_get_data_addr(
		v->var.win[1].mlx_img, &(v->var.win[1].bpp), &(v->var.win[1].s_l),
		&(v->var.win[1].endian))))
		return (0);
	if (!(mlx_put_image_to_window(v->w.mlx_ptr, v->w.mlx_win,
	v->var.win[1].mlx_img, 50, 25)))
		return (ft_error(v, "Put image error"));
	return (1);
}

int		load_textures(t_var *v)
{
	int width;
	int height;

	if (!(v->text[0].img = mlx_xpm_file_to_image(v->w.mlx_ptr,
		"./images/740.xpm", &width, &height)))
		return (ft_error(v, "Loading file error"));
	v->text[0].my_texture_string = mlx_get_data_addr(v->text[0].img,
		&(v->text[0].bpp), &(v->text[0].s_l), &(v->text[0].endian));
	if (!(v->text[1].img = mlx_xpm_file_to_image(v->w.mlx_ptr,
		"./images/741.xpm", &width, &height)))
		return (ft_error(v, "Loading file error"));
	v->text[1].my_texture_string = mlx_get_data_addr(v->text[1].img,
		&(v->text[1].bpp), &(v->text[1].s_l), &(v->text[1].endian));
	if (!(v->text[2].img = mlx_xpm_file_to_image(v->w.mlx_ptr,
		"./images/742.xpm", &width, &height)))
		return (ft_error(v, "Loading file error"));
	v->text[2].my_texture_string = mlx_get_data_addr(v->text[2].img,
		&(v->text[2].bpp), &(v->text[2].s_l), &(v->text[2].endian));
	if (!(v->text[3].img = mlx_xpm_file_to_image(v->w.mlx_ptr,
		"./images/745.xpm", &width, &height)))
		return (ft_error(v, "Loading file error"));
	v->text[3].my_texture_string = mlx_get_data_addr(v->text[3].img,
		&(v->text[3].bpp), &(v->text[3].s_l), &(v->text[3].endian));
	return (1);
}

int		create_window(t_var *v)
{
	if (!(v->w.mlx_ptr = mlx_init()))
		return (ft_error(v, "Mlx init error"));
	if (!(v->w.mlx_win = mlx_new_window(v->w.mlx_ptr, WIDTH, HEIGHT,
	"wolf3d")))
		return (ft_error(v, "New window error"));
	return (1);
}
