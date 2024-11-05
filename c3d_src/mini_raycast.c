/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:03:59 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/05 08:21:27 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	r_put_pixel(t_data **data, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = (y * (*data)->mini_size_line) + (x * ((*data)->mini_bite_per_pixel / 8));
	(*data)->mini_addr[pixel_index] = color & 0xFF;
	(*data)->mini_addr[pixel_index + 1] = (color >> 8) & 0xFF;
	(*data)->mini_addr[pixel_index + 2] = (color >> 16) & 0xFF;
}

int	r_init_ray(t_data **data, t_raycast **ray, int x)
{
	if ((*data)->player_x < 0 || (*data)->player_x > (*data)->m_wid
		|| (*data)->player_y < 0 || (*data)->player_y > (*data)->m_hei)
		return (1);
	(*ray)->camera_x = 2 * x / (double)(W_HEIGHT) - 1;
	(*ray)->ray_dir_x = (*data)->dir_x + (*data)->plane_x * (*ray)->camera_x;
	(*ray)->ray_dir_y = (*data)->dir_y + (*data)->plane_y * (*ray)->camera_x;
	return (0);
}

void	r_hit_wall(t_data **data, t_raycast **ray)
{
	double	ray_x;
	double	ray_y;
	double	step_size;

	step_size = 0.05;
	ray_x = (*data)->player_x;
	ray_y = (*data)->player_y;
	while (1)
	{
		(*ray)->map_x = (int)ray_x;
		(*ray)->map_y = (int)ray_y;
		if ((*data)->map[(*ray)->map_y][(*ray)->map_x] == '1' || (*data)->map[(*ray)->map_y][(*ray)->map_x] == 'D')
			break;
		int mini_x = (int)(ray_x * MINI_MULT);
		int mini_y = (int)(ray_y * MINI_MULT);
		r_put_pixel(data, mini_x, mini_y, 0x00FFAA);
		ray_x += (*ray)->ray_dir_x * step_size;
		ray_y += (*ray)->ray_dir_y * step_size;
	}
}

void	 render_raycast(t_data **data)
{
	int			x;
	t_raycast	*ray;

	x = 0;
	while (x < W_WIDTH)
	{
		ray = malloc (sizeof(t_raycast));
		if (r_init_ray(data, &ray, x) == 1)
			break ;
		r_hit_wall(data, &ray);
		free(ray);
		x++;
	}
}
