/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:55:41 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/19 11:44:36 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	check_cub(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 5)
		c_error("Not a .cub!");
	if (av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c'
		|| av[len - 4] != '.')
		c_error("Not a .cub!");
}

void	check_char(t_data **data)
{
	int	y;
	int	x;

	y = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
		{
			if ((*data)->map[y][x] != '0' && (*data)->map[y][x] != '1'
				&& (*data)->map[y][x] != 'N' && (*data)->map[y][x] != 'S'
				&& (*data)->map[y][x] != 'E' && (*data)->map[y][x] != 'W'
				&& (*data)->map[y][x] != '\n' && (*data)->map[y][x] != ' '
				&& (*data)->map[y][x] != 'D')
				c_error("Bad char in map!");
			x++;
		}
		y++;
	}
}

void	check_map(t_data **data)
{
	check_char(data);
	check_close(data);
}
