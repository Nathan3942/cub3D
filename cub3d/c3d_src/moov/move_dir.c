/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:27:20 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/19 16:11:05 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	move_down(t_data **data)
{
	if ((*data)->m_down == true)
	{
		if ((*data)->map[(int)((*data)->player_y - (*data)->dir_y * 0.4)]
			[(int)(*data)->player_x] != '1')
			(*data)->player_y -= (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)]
			[(int)((*data)->player_x - (*data)->dir_x * 0.4)] != '1')
			(*data)->player_x -= (*data)->dir_x * 0.1;
	}
}

void	move(t_data **data)
{
	if ((*data)->m_up == true)
	{
		if ((*data)->map[(int)((*data)->player_y + (*data)->dir_y * 0.4)]
			[(int)(*data)->player_x] != '1')
			(*data)->player_y += (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)]
			[(int)((*data)->player_x + (*data)->dir_x * 0.4)] != '1')
			(*data)->player_x += (*data)->dir_x * 0.1;
	}
	move_down(data);
}

void	move_right(t_data **data)
{
	if ((*data)->m_right == true)
	{
		if ((*data)->map[(int)((*data)->player_y - (*data)->dir_x * 0.4)]
			[(int)(*data)->player_x] != '1')
			(*data)->player_y -= (*data)->dir_x * 0.1;
		if ((*data)->map[(int)(*data)->player_y]
			[(int)((*data)->player_x - -(*data)->dir_y * 0.4)] != '1')
			(*data)->player_x -= -(*data)->dir_y * 0.1;
	}
}

void	move_lat(t_data **data)
{
	if ((*data)->m_left == true)
	{
		if ((*data)->map[(int)((*data)->player_y + (*data)->dir_x * 0.4)]
			[(int)(*data)->player_x] != '1')
			(*data)->player_y += (*data)->dir_x * 0.1;
		if ((*data)->map[(int)(*data)->player_y]
			[(int)((*data)->player_x + -(*data)->dir_y * 0.4)] != '1')
			(*data)->player_x += -(*data)->dir_y * 0.1;
	}
	move_right(data);
}
