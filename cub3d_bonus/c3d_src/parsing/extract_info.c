/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:12:03 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/19 11:34:25 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	extract_color(t_data **data, char **buf, int (*nb_txt)[2])
{
	char	**rgb;

	rgb = NULL;
	if (ft_strequal(buf[0], "F") == 0)
	{
		rgb = ft_split(buf[1], ',');
		if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
			c_error("Bad link color!");
		(*data)->txt_ground = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8)
			+ ft_atoi(rgb[2]);
		(*nb_txt)[1]++;
	}
	else if (ft_strequal(buf[0], "C") == 0)
	{
		rgb = ft_split(buf[1], ',');
		if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
			c_error("Bad link color!");
		(*data)->txt_ceiling = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8)
			+ ft_atoi(rgb[2]);
		(*nb_txt)[1]++;
	}
	if (rgb != NULL)
		ft_free_tab(rgb);
}

void	extract_texture(t_data **data, char **buf, int (*nb_txt)[2])
{
	extract_north(data, buf, nb_txt);
	extract_south(data, buf, nb_txt);
	extract_east(data, buf, nb_txt);
	extract_west(data, buf, nb_txt);
	extract_door(data, buf, nb_txt);
	extract_color(data, buf, nb_txt);
}

void	setup_extract(t_data **data, char *av, char *buffer, int (*nb_txt)[2])
{
	int		fd;
	char	**buf;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		c_error("File does not exist!");
	buffer = gnl(fd, buffer);
	buf = ft_split_link(buffer, ' ');
	while (buffer != NULL && ft_isdigit(first_num(buffer)) != 1)
	{
		if (buf[0] == NULL)
		{
			buffer = gnl(fd, buffer);
			continue ;
		}
		extract_texture(data, buf, nb_txt);
		buffer = gnl(fd, buffer);
		ft_free_tab(buf);
		buf = ft_split_link(buffer, ' ');
	}
	ft_free_tab(buf);
	ft_extrac_map(fd, buffer, data);
}

void	extract_info(t_data **data, char *av, char *buffer)
{
	int	nb_txt[2];

	nb_txt[0] = 0;
	nb_txt[1] = 0;
	setup_extract(data, av, buffer, &nb_txt);
	if (nb_txt[0] != 5)
		c_error("Missing texture!");
	if (nb_txt[1] != 2)
		c_error("Missing color!");
}
