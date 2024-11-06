/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:02:05 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/06 17:05:37 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	close_door(t_data **data)
{
	if ((*data)->player_x <= 0 || (*data)->player_y <= 0)
		return ;
	if ((*data)->dir_y < 0 && (*data)->map[(int)(*data)->player_y - 1]
			[(int)(*data)->player_x] == 'C')
		(*data)->map[(int)(*data)->player_y - 1][(int)(*data)->player_x] = 'D';
	if ((*data)->dir_y > 0 && (*data)->map[(int)(*data)->player_y + 1]
			[(int)(*data)->player_x] == 'C')
		(*data)->map[(int)(*data)->player_y + 1][(int)(*data)->player_x] = 'D';
	if ((*data)->dir_x < 0 && (*data)->map[(int)(*data)->player_y]
			[(int)(*data)->player_x - 1] == 'C')
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x - 1] = 'D';
	if ((*data)->dir_x > 0 && (*data)->map[(int)(*data)->player_y]
			[(int)(*data)->player_x + 1] == 'C')
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x + 1] = 'D';
}

int	open_door_bis(t_data **data)
{
	if ((*data)->dir_x < 0 && (*data)->map[(int)(*data)->player_y]
			[(int)(*data)->player_x - 1] == 'D')
	{
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x - 1] = 'C';
		return (1);
	}
	if ((*data)->dir_x > 0 && (*data)->map[(int)(*data)->player_y]
			[(int)(*data)->player_x + 1] == 'D')
	{
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x + 1] = 'C';
		return (1);
	}
	return (0);
}

int	open_door(t_data **data)
{
	if ((*data)->player_x <= 0 || (*data)->player_y <= 0)
		return (0);
	if ((*data)->dir_y < 0 && (*data)->map[(int)(*data)->player_y - 1]
			[(int)(*data)->player_x] == 'D')
	{
		(*data)->map[(int)(*data)->player_y - 1][(int)(*data)->player_x] = 'C';
		return (1);
	}
	if ((*data)->dir_y > 0 && (*data)->map[(int)(*data)->player_y + 1]
			[(int)(*data)->player_x] == 'D')
	{
		(*data)->map[(int)(*data)->player_y + 1][(int)(*data)->player_x] = 'C';
		return (1);
	}
	if (open_door_bis(data) == 1)
		return (1);
	return (0);
}

void	door(t_data **data)
{
	if (open_door(data) == 1)
		return ;
	else
		close_door(data);
}
