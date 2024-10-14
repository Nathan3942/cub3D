/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:46 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/14 18:18:54 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	calculate_window(t_data **data)
{
	int	x;
	int	x_tmp;
	int	y;

	y = 0;
	x_tmp = 0;
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

void	copy_start(t_data **data)
{
	int	i;

	(*data)->mapbis = (char **)malloc(((*data)->m_hei + 3) * sizeof(char *));
	(*data)->mapbis[0] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while ((*data)->map[0][i] != '\0')
		(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i] = '\0';
}

void	copy_end(t_data **data, int i, int j)
{
	(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while (i < (*data)->m_wid + 2)
		(*data)->mapbis[j][i++] = '0';
	(*data)->mapbis[j][i] = '\0';
	j++;
	(*data)->mapbis[j] = NULL;
}

void	copymap(t_data **data)
{
	int	i;
	int	j;

	j = 1;
	copy_start(data);
	while ((*data)->map[j - 1] != NULL)
	{
		i = 1;
		(*data)->mapbis[j] = (char *)malloc
			(((*data)->m_wid + 3) * sizeof(char));
		while ((*data)->map[j - 1][i - 1] != '\0')
		{
			(*data)->mapbis[j][0] = '0';
			(*data)->mapbis[j][i] = (*data)->map[j - 1][i - 1];
			i++;
		}
		(*data)->mapbis[j][i] = '0';
		(*data)->mapbis[j][i + 1] = '\0';
		j++;
	}
	copy_end(data, i, j);
}

void	init_data(char *av, t_data **data, char *buffer)
{
	check_cub(av);
	(*data)->mlx_ptr = mlx_init();
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr, W_WIDTH, W_HEIGHT,
			"Cub3d des gros BOOOOWGOS");
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
	extract_info(data, av, buffer);
	if ((*data)->txt_north == NULL)
		error("Empty file\n");
	calculate_window(data);
	calculate_pos_player(data);
	copymap(data);
}
