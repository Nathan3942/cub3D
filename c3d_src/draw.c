/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:00:45 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/14 17:13:02 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	draw_ceiling(t_data **data, t_raycast **ray, int x)
{
	int	y;
	int	color;
	int	pixel_index;

	y = 0;
	color = (*data)->txt_ceiling;
	while (y < (*ray)->draw_start)
	{
		pixel_index = (y * (*data)->size_line)
			+ (x * ((*data)->bite_per_pixel / 8));
		(*data)->mlx_address[pixel_index] = color & 0xFF;
		(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
		(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
		y++;
	}
}

void	draw_ground(t_data **data, t_raycast **ray, int x)
{
	int	y;
	int	color;
	int	pixel_index;

	y = (*ray)->draw_end;
	color = (*data)->txt_ground;
	while (y < W_HEIGHT)
	{
		pixel_index = (y * (*data)->size_line)
			+ (x * ((*data)->bite_per_pixel / 8));
		(*data)->mlx_address[pixel_index] = color & 0xFF;
		(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
		(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
		y++;
	}
}

void	draw_texture(t_data **data, t_raycast **ray, int x, t_texture *txt)
{
	int	y;
	int	tex_y;
	int	color;
	int	pixel_index;

	draw_ceiling(data, ray, x);
	y = (*ray)->draw_start;
	while (y < (*ray)->draw_end)
	{
		tex_y = (((y * 256 - W_HEIGHT * 128 + (*ray)->line_height * 128)
					* (*data)->hei) / (*ray)->line_height) / 256;
		color = *(int *)(txt->txt_data + (tex_y * txt->size_line
					+ (*ray)->tex_x * (txt->bits_per_pixel / 8)));
		pixel_index = (y * (*data)->size_line)
			+ (x * ((*data)->bite_per_pixel / 8));
		(*data)->mlx_address[pixel_index] = color & 0xFF;
		(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
		(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
		y++;
	}
	draw_ground(data, ray, x);
}

void	draw_wall(t_data **data, t_raycast **ray, int x)
{
	if ((*ray)->hit == 2)
		draw_texture(data, ray, x, (*data)->txt_door);
	else if ((*ray)->side == 1 && (*ray)->ray_dir_y < 0)
		draw_texture(data, ray, x, (*data)->txt_south);
	else if ((*ray)->side == 1 && (*ray)->ray_dir_y > 0)
		draw_texture(data, ray, x, (*data)->txt_north);
	else if ((*ray)->side == 0 && (*ray)->ray_dir_x > 0)
		draw_texture(data, ray, x, (*data)->txt_east);
	else
		draw_texture(data, ray, x, (*data)->txt_west);
}
