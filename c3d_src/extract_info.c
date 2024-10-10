/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:12:03 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/10 17:30:29 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	extract_color(t_data **data, char **buf)
{
	char	**rgb;

	rgb = NULL;
	if (ft_strequal(buf[0], "F") == 0)
	{
		rgb = ft_split(buf[1], ',');
		(*data)->txt_ground = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8)
			+ ft_atoi(rgb[2]);
	}
	else if (ft_strequal(buf[0], "C") == 0)
	{
		rgb = ft_split(buf[1], ',');
		(*data)->txt_ceiling = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8)
			+ ft_atoi(rgb[2]);
	}
	if (rgb != NULL)
		ft_free_tab(rgb);
}

void	extract_texture(t_data **data, char **buf)
{
	if (ft_strequal(buf[0], "NO") == 0)
	{
		(*data)->txt_north = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_north->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		//a faire pour tout avec un exit clean
		if (!(*data)->txt_north->txt_img)
		{
			ft_putendl_fd("Error link texture", 1);
			exit(1);
		}
		(*data)->txt_north->txt_data = mlx_get_data_addr((*data)->txt_north->txt_img, &(*data)->txt_north->bits_per_pixel, &(*data)->txt_north->size_line, &(*data)->txt_north->endianl);
	}
	else if (ft_strequal(buf[0], "SO") == 0)
	{
		(*data)->txt_south = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_south->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_south->txt_img)
		{
			ft_putendl_fd("Error link texture", 1);
			exit(1);
		}
		(*data)->txt_south->txt_data = mlx_get_data_addr((*data)->txt_south->txt_img, &(*data)->txt_south->bits_per_pixel, &(*data)->txt_south->size_line, &(*data)->txt_south->endianl);
	}
	else if (ft_strequal(buf[0], "WE") == 0)
	{
		(*data)->txt_west = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_west->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_west->txt_img)
		{
			ft_putendl_fd("Error link texture", 1);
			exit(1);
		}
		(*data)->txt_west->txt_data = mlx_get_data_addr((*data)->txt_west->txt_img, &(*data)->txt_west->bits_per_pixel, &(*data)->txt_west->size_line, &(*data)->txt_west->endianl);
	}
	else if (ft_strequal(buf[0], "EA") == 0)
	{
		(*data)->txt_east = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_east->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_east->txt_img)
		{
			ft_putendl_fd("Error link texture", 1);
			exit(1);
		}
		(*data)->txt_east->txt_data = mlx_get_data_addr((*data)->txt_east->txt_img, &(*data)->txt_east->bits_per_pixel, &(*data)->txt_east->size_line, &(*data)->txt_east->endianl);
	}
	else if (ft_strequal(buf[0], "DO") == 0)
	{
		(*data)->txt_door = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_door->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		if (!(*data)->txt_door->txt_img)
		{
			ft_putendl_fd("Error link texture", 1);
			exit(1);
		}
		(*data)->txt_door->txt_data = mlx_get_data_addr((*data)->txt_door->txt_img, &(*data)->txt_door->bits_per_pixel, &(*data)->txt_door->size_line, &(*data)->txt_door->endianl);
	}
	extract_color(data, buf);
}

void	extract_info(t_data **data, char *av, char *buffer)
{
	int		fd;
	char	**buf;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Erorr : file does not exist\n", 1);
		exit(1);
	}
	buffer = gnl(fd, buffer);
	buf = ft_split_link(buffer, ' ');
	while (buffer != NULL && ft_isdigit(first_num(buffer)) != 1)
	{
		if (buf[0] == NULL)
		{
			buffer = gnl(fd, buffer);
			continue ;
		}
		extract_texture(data, buf);
		buffer = gnl(fd, buffer);
		ft_free_tab(buf);
		buf = ft_split_link(buffer, ' ');
	}
	ft_free_tab(buf);
	ft_extrac_map(fd, buffer, data);
}
