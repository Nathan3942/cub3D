/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 04:13:38 by ichpakov          #+#    #+#             */
/*   Updated: 2024/10/01 20:00:02 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	move(t_data **data, int keycode)
{
	if (keycode == 119)
	{
		if ((*data)->map[(int)((*data)->player_y + (*data)->dir_y * 0.1)][(int)(*data)->player_x] != '1')
			(*data)->player_y += (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x + (*data)->dir_x * 0.1)] != '1')
			(*data)->player_x += (*data)->dir_x * 0.1;
	}
	if (keycode == 115)
	{
		if ((*data)->map[(int)((*data)->player_y - (*data)->dir_y * 0.1)][(int)(*data)->player_x] != '1')
			(*data)->player_y -= (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x - (*data)->dir_x * 0.1)] != '1')
			(*data)->player_x -= (*data)->dir_x * 0.1;
	}
}

void	turn(t_data **data, int keycode)
{
	double	old_dir;
	double	old_plane;

	old_dir = 0;
	old_plane = 0;
	if (keycode == 97)
	{
		old_dir = (*data)->dir_x;
		(*data)->dir_x = (*data)->dir_x * cos(-0.1) - (*data)->dir_y * sin(-0.1);
		(*data)->dir_y = old_dir * sin(-0.1) + (*data)->dir_y * cos(-0.1);
		old_plane = (*data)->plane_x;
		(*data)->plane_x = (*data)->plane_x * cos(-0.1) - (*data)->plane_y * sin(-0.1);
		(*data)->plane_y = old_plane * sin(-0.1) + (*data)->plane_y * cos(-0.1);
	}
	if (keycode == 100)
	{
		old_dir = (*data)->dir_x;
		(*data)->dir_x = (*data)->dir_x * cos(0.1) - (*data)->dir_y * sin(0.1);
		(*data)->dir_y = old_dir * sin(0.1) + (*data)->dir_y * cos(0.1);
		old_plane = (*data)->plane_x;
		(*data)->plane_x = (*data)->plane_x * cos(0.1) - (*data)->plane_y * sin(0.1);
		(*data)->plane_y = old_plane * sin(0.1) + (*data)->plane_y * cos(0.1);
	}
}

int    key_hook(int keycode, t_data **data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
		ft_putstr_fd("EXIT", 1);
		free_all(data);
		exit(0);
	}
	move(data, keycode);
	turn(data, keycode);
	return (0);
}

//Exit avec la croix de la window
int exit_1(t_data **data)
{
	ft_putstr_fd("EXIT\n", 1);
	mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
	free_all(data);
	exit(0);
}

int main(int ac, char **av)
{
	t_data  *data;
  	char    buffer[9999];
	
	if (ac != 2)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	init_data(av[1], &data, buffer);
	
	// print_para(data);
	check_map(&data);
	mlx_loop_hook(data->mlx_ptr, (void *)render, &data);
	mlx_hook(data->win_ptr, 17, 0, exit_1, &data);
	mlx_hook(data->win_ptr, 2, 1L<<0, key_hook, &data);
	mlx_loop(data->mlx_ptr);
	free_all(&data);
	return (0);
}

	// data.s = "Kaca";
		// data.mlx_ptr = mlx_init();
	// data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Cub3d des gros BOOOOWGOS");
	// mlx_string_put(data.mlx_ptr, data.win_ptr, 395, 295, 0xFFFFFFF, data.s);
	// mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	// mlx_hook(data.win_ptr, 17, 0, exit_1, &data);
	//key_hook(K_ESC, &data, mlx_ptr, win_ptr);
	//mlx_loop(data.mlx_ptr);