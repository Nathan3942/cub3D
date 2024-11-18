/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:46 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/18 19:48:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	calculate_window(t_data **data)
{
	int	x;
	int	x_tmp;
	int	y;

	y = 0;
	x_tmp = 0;
	if ((*data)->map == NULL)
	{
		ft_putendl_fd("Error no map!", 1);
		exit(1);
	}
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
			x++;
		if (x > x_tmp)
			x_tmp = x;
		y++;
	}
	(*data)->m_wid = x_tmp;
	(*data)->m_hei = y;
}

void	set_value(t_data **data)
{
	(*data)->map = NULL;
	(*data)->txt_north = NULL;
	(*data)->txt_south = NULL;
	(*data)->txt_west = NULL;
	(*data)->txt_east = NULL;
	(*data)->txt_door = NULL;
	(*data)->index_img = 3;
	(*data)->wid = 500;
	(*data)->hei = 500;
	(*data)->x_mouse = -1;
	(*data)->m_up = false;
	(*data)->m_down = false;
	(*data)->m_left = false;
	(*data)->m_right = false;
	(*data)->t_left = false;
	(*data)->t_right = false;
	(*data)->player_x = -1;
}

void	init_data(char *av, t_data **data, char *buffer)
{
	check_cub(av);
	(*data)->mlx_ptr = mlx_init();
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr, W_WIDTH, W_HEIGHT,
			"Cub3d des gros BOOOOWGOS");
	set_value(data);
	extract_info(data, av, buffer);
	if ((*data)->txt_north == NULL)
		error("Empty file\n");
	calculate_window(data);
	calculate_pos_player(data);
	copymap(data);
}
