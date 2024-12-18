/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:46 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/20 17:40:16 by njeanbou         ###   ########.fr       */
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
		c_error("No map!", data);
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
	(*data)->mapbis = NULL;
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

void	calculate_mini_mult(t_data **data)
{
	int	biger;
	int	mult;

	mult = 25;
	if ((*data)->m_wid > (*data)->m_hei)
		biger = (*data)->m_wid;
	else
		biger = (*data)->m_hei;
	while (biger * mult > W_WIDTH * 0.4)
		mult--;
	(*data)->m_mult = mult;
}

void	init_data(char *av, t_data **data, char *buffer)
{
	set_value(data);
	check_cub(av, data);
	(*data)->mlx_ptr = mlx_init();
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr, W_WIDTH, W_HEIGHT,
			"Cub3d des gros BOOOOWGOS");
	extract_info(data, av, buffer);
	calculate_window(data);
	calculate_pos_player(data);
	calculate_mini_mult(data);
	copymap(data);
}
