/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:48:56 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/10 17:16:56 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

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
