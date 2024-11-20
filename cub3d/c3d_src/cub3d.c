/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 04:13:38 by ichpakov          #+#    #+#             */
/*   Updated: 2024/11/19 14:19:17 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

int	key_hook(int keycode, t_data **data)
{
	if (keycode == 65307)
	{
		ft_putstr_fd("EXIT\n", 1);
		free_all(data);
		exit(0);
	}
	if (keycode == 119)
		(*data)->m_up = true;
	if (keycode == 115)
		(*data)->m_down = true;
	if (keycode == 100)
		(*data)->m_left = true;
	if (keycode == 97)
		(*data)->m_right = true;
	if (keycode == 65361)
		(*data)->t_left = true;
	if (keycode == 65363)
		(*data)->t_right = true;
	return (0);
}

int	key_release(int keycode, t_data **data)
{
	if (keycode == 119)
		(*data)->m_up = false;
	if (keycode == 115)
		(*data)->m_down = false;
	if (keycode == 100)
		(*data)->m_left = false;
	if (keycode == 97)
		(*data)->m_right = false;
	if (keycode == 65361)
		(*data)->t_left = false;
	if (keycode == 65363)
		(*data)->t_right = false;
	return (0);
}

int	exit_1(t_data **data)
{
	ft_putstr_fd("EXIT\n", 1);
	free_all(data);
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	buffer[9999];

	if (ac != 2)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	init_data(av[1], &data, buffer);
	check_map(&data);
	mlx_loop_hook(data->mlx_ptr, (void *)render, &data);
	mlx_hook(data->win_ptr, 17, 0, exit_1, &data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, &data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release, &data);
	mlx_loop(data->mlx_ptr);
	free_all(&data);
	return (0);
}
