/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:48:56 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/06 17:06:34 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

int	init_ray(t_data **data, t_raycast **ray, int x)
{
	if ((*data)->player_x < 0 || (*data)->player_x > (*data)->m_wid
		|| (*data)->player_y < 0 || (*data)->player_y > (*data)->m_hei)
		return (1);
	(*ray)->camera_x = 2 * x / (double)W_WIDTH - 1;
	(*ray)->ray_dir_x = (*data)->dir_x + (*data)->plane_x * (*ray)->camera_x;
	(*ray)->ray_dir_y = (*data)->dir_y + (*data)->plane_y * (*ray)->camera_x;
	(*ray)->map_x = (int)(*data)->player_x;
	(*ray)->map_y = (int)(*data)->player_y;
	(*ray)->unit_dir_x = fabs(1 / (*ray)->ray_dir_x);
	(*ray)->unit_dir_y = fabs(1 / (*ray)->ray_dir_y);
	(*ray)->hit = 0;
	return (0);
}

void	side_dist(t_data **data, t_raycast **ray)
{
	if ((*ray)->ray_dir_x < 0)
	{
		(*ray)->step_x = -1;
		(*ray)->side_dist_x = ((*data)->player_x
				- (*ray)->map_x) * (*ray)->unit_dir_x;
	}
	else
	{
		(*ray)->step_x = 1;
		(*ray)->side_dist_x = ((*ray)->map_x + 1.0
				- (*data)->player_x) * (*ray)->unit_dir_x;
	}
	if ((*ray)->ray_dir_y < 0)
	{
		(*ray)->step_y = -1;
		(*ray)->side_dist_y = ((*data)->player_y
				- (*ray)->map_y) * (*ray)->unit_dir_y;
	}
	else
	{
		(*ray)->step_y = 1;
		(*ray)->side_dist_y = ((*ray)->map_y + 1.0
				- (*data)->player_y) * (*ray)->unit_dir_y;
	}
}

void	hit_wall(t_data **data, t_raycast **ray)
{
	while ((*ray)->hit == 0)
	{
		if ((*ray)->side_dist_x < (*ray)->side_dist_y)
		{
			(*ray)->side_dist_x += (*ray)->unit_dir_x;
			(*ray)->map_x += (*ray)->step_x;
			(*ray)->side = 0;
		}
		else
		{
			(*ray)->side_dist_y += (*ray)->unit_dir_y;
			(*ray)->map_y += (*ray)->step_y;
			(*ray)->side = 1;
		}
		if ((*data)->map[(*ray)->map_y][(*ray)->map_x] == '1')
			(*ray)->hit = 1;
		if ((*data)->map[(*ray)->map_y][(*ray)->map_x] == 'D')
			(*ray)->hit = 2;
	}
}

void	calcul_draw_line(t_data **data, t_raycast **ray)
{
	if ((*ray)->side == 0)
		(*ray)->perp_wall_dist = ((*ray)->map_x - (*data)->player_x
				+ (1 - (*ray)->step_x) / 2) / (*ray)->ray_dir_x;
	else
		(*ray)->perp_wall_dist = ((*ray)->map_y - (*data)->player_y
				+ (1 - (*ray)->step_y) / 2) / (*ray)->ray_dir_y;
	(*ray)->line_height = (int)(W_HEIGHT / (*ray)->perp_wall_dist);
	(*ray)->draw_start = -(*ray)->line_height / 2 + W_HEIGHT / 2;
	if ((*ray)->draw_start < 0)
		(*ray)->draw_start = 0;
	(*ray)->draw_end = (*ray)->line_height / 2 + W_HEIGHT / 2;
	if ((*ray)->draw_end >= W_HEIGHT)
		(*ray)->draw_end = W_HEIGHT - 1;
}

void	calcul_view_texture(t_data **data, t_raycast **ray)
{
	if ((*ray)->side == 0)
		(*ray)->wall_x = (*data)->player_y + (*ray)->perp_wall_dist
			* (*ray)->ray_dir_y;
	else
		(*ray)->wall_x = (*data)->player_x + (*ray)->perp_wall_dist
			* (*ray)->ray_dir_x;
	(*ray)->wall_x -= floor((*ray)->wall_x);
	(*ray)->tex_x = (int)((*ray)->wall_x * (double)(*data)->wid);
}
