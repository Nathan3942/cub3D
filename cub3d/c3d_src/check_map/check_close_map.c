/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:46:11 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/20 16:35:48 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

int	check_border(char **mapbis, int y, int x, int i)
{
	int	res;

	if (i != 0)
	{
		if (mapbis[y][x] == 'F' && i > 2)
			return (1);
		if ((y <= 0 || x <= 0 || mapbis[y][x + 1] == '\0'
			|| mapbis[y] == NULL || mapbis[y][x] != '1' || mapbis[y][x] == '2'))
			return (0);
	}
	(i)++;
	if (i == 1 || mapbis[y][x] == '1')
	{
		if (mapbis[y][x] != 'F')
			mapbis[y][x] = '2';
		res = (check_border(mapbis, y, x + 1, i)
				|| check_border(mapbis, y + 1, x, i)
				|| check_border(mapbis, y, x - 1, i)
				|| check_border(mapbis, y - 1, x, i));
		return (res);
	}
	return (0);
}

void	search_pos_player(t_data **data, int *y, int *x)
{
	while ((*data)->mapbis[*y] != NULL)
	{
		(*x) = 0;
		while ((*data)->mapbis[*y][*x] != '\0')
		{
			if ((*data)->mapbis[*y][*x] == 'N' || (*data)->mapbis[*y][*x] == 'S'
				|| (*data)->mapbis[*y][*x] == 'E'
				|| (*data)->mapbis[*y][*x] == 'W')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

int	check_perso(t_data **data, int y, int x)
{
	int	res;

	if ((*data)->mapbis[y][x] == '1' || (*data)->mapbis[y][x] == '3')
		return (0);
	if (y <= 0 || x <= 0 || y >= (*data)->m_hei + 1 || x >= (*data)->m_wid + 1)
		return (1);
	(*data)->mapbis[y][x] = '3';
	res = (check_perso(data, y + 1, x) || check_perso(data, y, x + 1)
			|| check_perso(data, y - 1, x) || check_perso(data, y, x - 1));
	return (res);
}

bool	map_close(t_data **data, int *y, int *x)
{
	int		i;
	int		pos_x;
	int		pos_y;

	i = 0;
	pos_y = 0;
	pos_x = 0;
	(*data)->mapbis[*y][*x] = 'F';
	search_pos_player(data, &pos_y, &pos_x);
	if (check_perso(data, pos_y, pos_x) == 0
		&& check_border((*data)->mapbis, *y, *x, i) == 1)
		return (true);
	else
		return (false);
}

void	check_close(t_data **data)
{
	int	y;
	int	x;

	y = 1;
	x = 1;
	while ((*data)->mapbis[y][x] != '1')
		x++;
	while ((*data)->mapbis[y][x] == '1' && ((*data)->mapbis[y][x + 1] != '1'
		|| (*data)->mapbis[y + 1][x] != '1'))
		x++;
	if (map_close(data, &y, &x) == false)
		c_error("Map not closed!", data);
}
