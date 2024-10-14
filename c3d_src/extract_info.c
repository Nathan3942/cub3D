/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:12:03 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/14 17:43:45 by njeanbou         ###   ########.fr       */
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
