/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 04:13:38 by ichpakov          #+#    #+#             */
/*   Updated: 2024/10/03 05:39:39 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	move(t_data **data, int keycode)
{
	if (keycode == 119)
	{
		if ((*data)->map[(int)((*data)->player_y + (*data)->dir_y * 0.2)][(int)(*data)->player_x] != '1'
			&& (*data)->map[(int)((*data)->player_y + (*data)->dir_y * 0.2)][(int)(*data)->player_x] != 'D')
			(*data)->player_y += (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x + (*data)->dir_x * 0.2)] != '1'
			&& (*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x + (*data)->dir_x * 0.2)] != 'D')
			(*data)->player_x += (*data)->dir_x * 0.1;
	}
	if (keycode == 115)
	{
		if ((*data)->map[(int)((*data)->player_y - (*data)->dir_y * 0.2)][(int)(*data)->player_x] != '1'
			&& (*data)->map[(int)((*data)->player_y - (*data)->dir_y * 0.2)][(int)(*data)->player_x] != 'D')
			(*data)->player_y -= (*data)->dir_y * 0.1;
		if ((*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x - (*data)->dir_x * 0.2)] != '1'
			&& (*data)->map[(int)((*data)->player_y)][(int)((*data)->player_x - (*data)->dir_x * 0.2)] != 'D')
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

void close_door(t_data **data)
{
	if ((*data)->player_x <= 0 || (*data)->player_y <= 0)
		return ;
	if ((*data)->dir_y < 0 && (*data)->map[(int)(*data)->player_y - 1][(int)(*data)->player_x] == 'C')
		(*data)->map[(int)(*data)->player_y - 1][(int)(*data)->player_x] = 'D';
	if ((*data)->dir_y > 0 && (*data)->map[(int)(*data)->player_y + 1][(int)(*data)->player_x] == 'C')
		(*data)->map[(int)(*data)->player_y + 1][(int)(*data)->player_x] = 'D';
	if ((*data)->dir_x < 0 && (*data)->map[(int)(*data)->player_y][(int)(*data)->player_x - 1] == 'C')
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x - 1] = 'D';
	if ((*data)->dir_x > 0 && (*data)->map[(int)(*data)->player_y][(int)(*data)->player_x + 1] == 'C')
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x + 1] = 'D';
}

int	open_door(t_data **data)
{
	if ((*data)->player_x <= 0 || (*data)->player_y <= 0)
		return (0);
	if ((*data)->dir_y < 0 && (*data)->map[(int)(*data)->player_y - 1][(int)(*data)->player_x] == 'D')
	{
		(*data)->map[(int)(*data)->player_y - 1][(int)(*data)->player_x] = 'C';
		return (1);
	}
	if ((*data)->dir_y > 0 && (*data)->map[(int)(*data)->player_y + 1][(int)(*data)->player_x] == 'D')
	{
		(*data)->map[(int)(*data)->player_y + 1][(int)(*data)->player_x] = 'C';
		return (1);
	}
	if ((*data)->dir_x < 0 && (*data)->map[(int)(*data)->player_y][(int)(*data)->player_x - 1] == 'D')
	{
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x - 1] = 'C';
		return (1);
	}
	if ((*data)->dir_x > 0 && (*data)->map[(int)(*data)->player_y][(int)(*data)->player_x + 1] == 'D')
	{
		(*data)->map[(int)(*data)->player_y][(int)(*data)->player_x + 1] = 'C';
		return (1);
	}
	return (0);
}

void	door(t_data **data)
{
	if (open_door(data) == 1)
		return ;
	else
		close_door(data);
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
	if (keycode == 101)
		door(data);
		
	printf("%d : %c\n", keycode, (*data)->map[(int)(*data)->player_y][(int)(*data)->player_x]);
	move(data, keycode);
	turn(data, keycode);
	return (0);
}

int mouse_move(int x, int y, t_data **data)
{
	double	old_dir;
	double	old_plane;
	double	rotate_speed;
	double	sensi;

	sensi = 0.001;
	if ((*data)->x_mouse == -1)
	{
		printf("Mouse moved to: (%d, %d)\n", x, y);
		(*data)->x_mouse = x;
	}
	rotate_speed = (x - (*data)->x_mouse) * sensi;
	if (x < (*data)->x_mouse)
	{
		old_dir = (*data)->dir_x;
		(*data)->dir_x = (*data)->dir_x * cos(rotate_speed) - (*data)->dir_y * sin(rotate_speed);
		(*data)->dir_y = old_dir * sin(rotate_speed) + (*data)->dir_y * cos(rotate_speed);
		old_plane = (*data)->plane_x;
		(*data)->plane_x = (*data)->plane_x * cos(rotate_speed) - (*data)->plane_y * sin(rotate_speed);
		(*data)->plane_y = old_plane * sin(rotate_speed) + (*data)->plane_y * cos(rotate_speed);
	}
	else if (x > (*data)->x_mouse)
	{
		old_dir = (*data)->dir_x;
		(*data)->dir_x = (*data)->dir_x * cos(rotate_speed) - (*data)->dir_y * sin(rotate_speed);
		(*data)->dir_y = old_dir * sin(rotate_speed) + (*data)->dir_y * cos(rotate_speed);
		old_plane = (*data)->plane_x;
		(*data)->plane_x = (*data)->plane_x * cos(rotate_speed) - (*data)->plane_y * sin(rotate_speed);
		(*data)->plane_y = old_plane * sin(rotate_speed) + (*data)->plane_y * cos(rotate_speed);
	}
	(*data)->x_mouse = x;    
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
	check_map(&data);
	print_para(data);
	mlx_loop_hook(data->mlx_ptr, (void *)render, &data);
	mlx_hook(data->win_ptr, 17, 0, exit_1, &data);
	mlx_hook(data->win_ptr, 2, 1L<<0, key_hook, &data);
	mlx_hook(data->win_ptr, 6, 1L<<6, mouse_move, &data);
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