/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:55:41 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/10 17:18:48 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	check_cub(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 5)
	{
		ft_putstr_fd("Error .cub\n", 1);
		exit(1);
	}
	if (av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c'
		|| av[len - 4] != '.')
	{
		ft_putstr_fd("Error .cub\n", 1);
		exit(1);
	}
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
			{
				ft_putstr_fd("Error wrong char in map\n", 1);
				exit(1);
			}
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
