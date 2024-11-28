/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:14:41 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/28 17:45:12 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

static void	extract_floor(t_data **data, char **buf,
		int (*nb_txt)[2], char **rgb)
{
	rgb = ft_split(buf[1], ',');
	if (!rgb || rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
	{
		ft_free_tab(rgb);
		ft_free_tab(buf);
		c_error("Bad link color!", data);
	}
	(*data)->txt_ground = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8)
		+ ft_atoi(rgb[2]);
	(*nb_txt)[1]++;
	if (rgb != NULL)
		ft_free_tab(rgb);
}

void	extract_color(t_data **data, char **buf, int (*nb_txt)[2])
{
	char	**rgb;

	rgb = NULL;
	if (ft_strequal(buf[0], "F") == 0)
	{
		extract_floor(data, buf, nb_txt, rgb);
	}
	else if (ft_strequal(buf[0], "C") == 0)
	{
		rgb = ft_split(buf[1], ',');
		if (!rgb || rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
		{
			ft_free_tab(rgb);
			ft_free_tab(buf);
			c_error("Bad link color!", data);
		}
		(*data)->txt_ceiling = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8)
			+ ft_atoi(rgb[2]);
		(*nb_txt)[1]++;
	}
	if (rgb != NULL)
		ft_free_tab(rgb);
}
