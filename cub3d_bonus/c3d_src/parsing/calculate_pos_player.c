/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pos_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:56:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/20 17:43:50 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	set_dir_bis(t_data **data, char c)
{
	if (c == 'E')
	{
		(*data)->dir_x = 1;
		(*data)->dir_y = 0;
		(*data)->plane_x = 0;
		(*data)->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		(*data)->dir_x = -1;
		(*data)->dir_y = 0;
		(*data)->plane_x = 0;
		(*data)->plane_y = -0.66;
	}
}

void	set_dir(t_data **data, char c)
{
	if (c == 'N')
	{
		(*data)->dir_x = 0;
		(*data)->dir_y = -1;
		(*data)->plane_x = 0.66;
		(*data)->plane_y = 0;
	}
	else if (c == 'S')
	{
		(*data)->dir_x = 0;
		(*data)->dir_y = 1;
		(*data)->plane_x = -0.66;
		(*data)->plane_y = 0;
	}
	set_dir_bis(data, c);
}

void	calculate_pos_player(t_data **data)
{
	int		y;
	int		x;
	int		nb_player;

	nb_player = 0;
	y = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
		{
			if ((*data)->map[y][x] == 'N' || (*data)->map[y][x] == 'S'
				|| (*data)->map[y][x] == 'E' || (*data)->map[y][x] == 'W')
			{
				(*data)->player_x = (double)x + 0.5;
				(*data)->player_y = (double)y + 0.5;
				set_dir(data, (*data)->map[y][x]);
				nb_player++;
			}
			x++;
		}
		y++;
	}
	if ((*data)->player_x == -1 || nb_player != 1)
		c_error("No or to many player in map!", data);
}
