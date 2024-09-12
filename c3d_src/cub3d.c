/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 04:13:38 by ichpakov          #+#    #+#             */
/*   Updated: 2024/09/12 08:00:20 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

int    key_hook(int keycode, t_data **data)
{
	if (keycode == 53)
	{
		mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
		ft_putstr_fd("EXIT", 1);
		free_all(data);
		exit(0);
	}
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
	printf("%d, %d\n", data->w_hei, data->w_wei);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->w_wei, data->w_hei, "Cub3d des gros BOOOOWGOS");
	
	print_para(data);
	check_map(&data);
	creat_map(&data);
	mlx_hook(data->win_ptr, 17, 0, exit_1, &data);
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