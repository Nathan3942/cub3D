/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:02:24 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/07 20:06:54 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	move(t_data **data)
{
	if ((*data)->m_up == true)
	{
		if ((*data)->map[(int)((*data)->player_y + (*data)->dir_y * 0.2)][(int)(*data)->player_x] != '1'
			&& (*data)->map[(int)((*data)->player_y + (*data)->dir_y * 0.2)][(int)(*data)->player_x] != 'D')
			(*data)->player_y += (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x + (*data)->dir_x * 0.2)] != '1'
			&& (*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x + (*data)->dir_x * 0.2)] != 'D')
			(*data)->player_x += (*data)->dir_x * 0.1;
	}
	if ((*data)->m_down == true)
	{
		if ((*data)->map[(int)((*data)->player_y - (*data)->dir_y * 0.2)][(int)(*data)->player_x] != '1'
			&& (*data)->map[(int)((*data)->player_y - (*data)->dir_y * 0.2)][(int)(*data)->player_x] != 'D')
			(*data)->player_y -= (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x - (*data)->dir_x * 0.2)] != '1'
			&& (*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x - (*data)->dir_x * 0.2)] != 'D')
			(*data)->player_x -= (*data)->dir_x * 0.1;
	}
}

void	move_lat(t_data **data)
{
	if ((*data)->m_left == true)
	{
		if ((*data)->map[(int)((*data)->player_y + (*data)->dir_x * 0.2)][(int)(*data)->player_x] != '1'
			&& (*data)->map[(int)((*data)->player_y + (*data)->dir_x * 0.2)][(int)(*data)->player_x] != 'D')
			(*data)->player_y += (*data)->dir_x * 0.1;
		if ((*data)->map[(int)(*data)->player_y][(int)((*data)->player_x + -(*data)->dir_y * 0.2)] != '1'
			&& (*data)->map[(int)(*data)->player_y][(int)((*data)->player_x + -(*data)->dir_y * 0.2)] != 'D')
			(*data)->player_x += -(*data)->dir_y * 0.1;
	}
	if ((*data)->m_right == true)
	{
		if ((*data)->map[(int)((*data)->player_y - (*data)->dir_x * 0.2)][(int)(*data)->player_x] != '1'
			&& (*data)->map[(int)((*data)->player_y - (*data)->dir_x * 0.2)][(int)(*data)->player_x] != 'D')
			(*data)->player_y -= (*data)->dir_x * 0.1;
		if ((*data)->map[(int)(*data)->player_y][(int)((*data)->player_x - -(*data)->dir_y * 0.2)] != '1'
			&& (*data)->map[(int)(*data)->player_y][(int)((*data)->player_x - -(*data)->dir_y * 0.2)] != 'D')
			(*data)->player_x -= -(*data)->dir_y * 0.1;
	}
}

void	turn(t_data **data)
{
	double	old_dir;
	double	old_plane;

	old_dir = 0;
	old_plane = 0;
	if ((*data)->t_left == true)
	{
		old_dir = (*data)->dir_x;
		(*data)->dir_x = (*data)->dir_x * cos(-0.1) - (*data)->dir_y * sin(-0.1);
		(*data)->dir_y = old_dir * sin(-0.1) + (*data)->dir_y * cos(-0.1);
		old_plane = (*data)->plane_x;
		(*data)->plane_x = (*data)->plane_x * cos(-0.1) - (*data)->plane_y * sin(-0.1);
		(*data)->plane_y = old_plane * sin(-0.1) + (*data)->plane_y * cos(-0.1);
	}
	if ((*data)->t_right == true)
	{
		old_dir = (*data)->dir_x;
		(*data)->dir_x = (*data)->dir_x * cos(0.1) - (*data)->dir_y * sin(0.1);
		(*data)->dir_y = old_dir * sin(0.1) + (*data)->dir_y * cos(0.1);
		old_plane = (*data)->plane_x;
		(*data)->plane_x = (*data)->plane_x * cos(0.1) - (*data)->plane_y * sin(0.1);
		(*data)->plane_y = old_plane * sin(0.1) + (*data)->plane_y * cos(0.1);
	}
}

void	input(t_data **data)
{
	move(data);
	move_lat(data);
	turn(data);
}