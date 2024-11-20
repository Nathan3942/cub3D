/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:39:11 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/19 12:18:47 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	extract_north(t_data **data, char **buf, int (*nb_txt)[2])
{
	if (ft_strequal(buf[0], "NO") == 0)
	{
		(*data)->txt_north = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_north->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr,
				buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_north->txt_img)
			c_error("Bad texture link!");
		(*data)->txt_north->txt_data = mlx_get_data_addr((*data)
				->txt_north->txt_img, &(*data)->txt_north->bits_per_pixel,
				&(*data)->txt_north->size_line, &(*data)->txt_north->endianl);
		(*nb_txt)[0]++;
	}
}

void	extract_south(t_data **data, char **buf, int (*nb_txt)[2])
{
	if (ft_strequal(buf[0], "SO") == 0)
	{
		(*data)->txt_south = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_south->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr,
				buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_south->txt_img)
			c_error("Bad texture link!");
		(*data)->txt_south->txt_data = mlx_get_data_addr((*data)
				->txt_south->txt_img, &(*data)->txt_south->bits_per_pixel,
				&(*data)->txt_south->size_line, &(*data)->txt_south->endianl);
		(*nb_txt)[0]++;
	}
}

void	extract_east(t_data **data, char **buf, int (*nb_txt)[2])
{
	if (ft_strequal(buf[0], "EA") == 0)
	{
		(*data)->txt_east = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_east->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr,
				buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_east->txt_img)
			c_error("Bad texture link!");
		(*data)->txt_east->txt_data = mlx_get_data_addr((*data)
				->txt_east->txt_img, &(*data)->txt_east->bits_per_pixel,
				&(*data)->txt_east->size_line, &(*data)->txt_east->endianl);
		(*nb_txt)[0]++;
	}
}

void	extract_west(t_data **data, char **buf, int (*nb_txt)[2])
{
	if (ft_strequal(buf[0], "WE") == 0)
	{
		(*data)->txt_west = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_west->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr,
				buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_west->txt_img)
			c_error("Bad texture link!");
		(*data)->txt_west->txt_data = mlx_get_data_addr((*data)
				->txt_west->txt_img, &(*data)->txt_west->bits_per_pixel,
				&(*data)->txt_west->size_line, &(*data)->txt_west->endianl);
		(*nb_txt)[0]++;
	}
}

void	extract_door(t_data **data, char **buf, int (*nb_txt)[2])
{
	if (ft_strequal(buf[0], "DO") == 0)
	{
		(*data)->txt_door = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_door->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr,
				buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_door->txt_img)
			c_error("Bad texture link!");
		(*data)->txt_door->txt_data = mlx_get_data_addr((*data)
				->txt_door->txt_img, &(*data)->txt_door->bits_per_pixel,
				&(*data)->txt_door->size_line, &(*data)->txt_door->endianl);
		(*nb_txt)[0]++;
	}
}
