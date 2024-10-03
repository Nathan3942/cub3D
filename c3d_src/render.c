/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:05:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/03 15:28:21 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

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
	// printf("data : %f, %f, %f, %f\n", (*data)->dir_x, (*data)->dir_y, (*data)->plane_x, (*data)->plane_y);
	// printf("cam %f, %f, %f\n", (*ray)->camera_x, (*ray)->ray_dir_x, (*ray)->ray_dir_y);
	// printf("Dir : %f, %f\nPlane : %f, %f\n", (*data)->dir_x, (*data)->dir_y, (*data)->plane_x, (*data)->plane_y);
	return (0);
}

void	side_dist(t_data **data, t_raycast **ray)
{
	if ((*ray)->ray_dir_x < 0)
	{
		(*ray)->step_x = -1;
		(*ray)->side_dist_x = ((*data)->player_x - (*ray)->map_x) * (*ray)->unit_dir_x;
	}
	else
	{
		(*ray)->step_x = 1;
		(*ray)->side_dist_x = ((*ray)->map_x + 1.0 - (*data)->player_x) * (*ray)->unit_dir_x;
	}
	if ((*ray)->ray_dir_y < 0)
	{
		(*ray)->step_y = -1;
		(*ray)->side_dist_y = ((*data)->player_y - (*ray)->map_y) * (*ray)->unit_dir_y;
	}
	else
	{
		(*ray)->step_y = 1;
		(*ray)->side_dist_y = ((*ray)->map_y + 1.0 - (*data)->player_y) * (*ray)->unit_dir_y;
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
		(*ray)->perp_wall_dist = ((*ray)->map_x - (*data)->player_x + (1 - (*ray)->step_x) / 2) / (*ray)->ray_dir_x;
	else
		(*ray)->perp_wall_dist = ((*ray)->map_y - (*data)->player_y + (1 - (*ray)->step_y) / 2) / (*ray)->ray_dir_y;
	(*ray)->line_height = (int)(W_HEIGHT / (*ray)->perp_wall_dist);
	(*ray)->draw_start = -(*ray)->line_height / 2 + W_HEIGHT / 2;
	if ((*ray)->draw_start < 0)
		(*ray)->draw_start = 0;
	(*ray)->draw_end = (*ray)->line_height / 2 + W_HEIGHT / 2;
	if ((*ray)->draw_end >= W_HEIGHT)
		(*ray)->draw_end = W_HEIGHT - 1;
	// printf("draw : %d, %d, %f\nmap : %d, %d\n", (*ray)->draw_start, (*ray)->draw_end, (*ray)->perp_wall_dist, (*ray)->map_x, (*ray)->map_y);
}

void	calcul_view_texture(t_data **data, t_raycast **ray)
{
	if ((*ray)->side == 0)
		(*ray)->wall_x = (*data)->player_y + (*ray)->perp_wall_dist * (*ray)->ray_dir_y;
	else
		(*ray)->wall_x = (*data)->player_x + (*ray)->perp_wall_dist * (*ray)->ray_dir_x;
	(*ray)->wall_x -= floor((*ray)->wall_x);
	(*ray)->tex_x = (int)((*ray)->wall_x * (double)(*data)->wid);
	// if ((*ray)->side == 0 && (*ray)->ray_dir_x > 0)
	// 	(*ray)->tex_x = (*data)->wid - (*ray)->tex_x - 1;
	// if ((*ray)->side == 1 && (*ray)->ray_dir_x < 0)
	// 	(*ray)->tex_x = (*data)->wid - (*ray)->tex_x - 1;
}

void	draw_ceiling(t_data **data, t_raycast **ray, int x)
{
	int	y;
	int color;
	int pixel_index;

	y = 0;
	color = (*data)->txt_ceiling;
	while (y < (*ray)->draw_start)
	{
		pixel_index = (y * (*data)->size_line) + (x * ((*data)->bite_per_pixel / 8));
		(*data)->mlx_address[pixel_index] = color & 0xFF;
		(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
		(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
		y++;
	}
}

void	draw_ground(t_data **data, t_raycast **ray, int x)
{
	int	y;
	int color;
	int pixel_index;

	y = (*ray)->draw_end;
	color = (*data)->txt_ground;
	while (y < W_HEIGHT)
	{
		pixel_index = (y * (*data)->size_line) + (x * ((*data)->bite_per_pixel / 8));
		(*data)->mlx_address[pixel_index] = color & 0xFF;
		(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
		(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
		y++;
	}
}

void	draw_texture(t_data **data, t_raycast **ray, int x, t_texture *txt)
{
	int	y;
	int tex_y;
	int color;
	int pixel_index;

	draw_ceiling(data, ray, x);
	y = (*ray)->draw_start;
	while (y < (*ray)->draw_end)
	{
		tex_y = (((y * 256 - W_HEIGHT * 128 + (*ray)->line_height * 128) * (*data)->hei) / (*ray)->line_height) / 256;
		color = *(int *)(txt->txt_data + (tex_y * txt->size_line + (*ray)->tex_x * (txt->bits_per_pixel / 8)));
		pixel_index = (y * (*data)->size_line) + (x * ((*data)->bite_per_pixel / 8));
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


void	ray_cast(t_data **data)
{
	int			x;
	t_raycast	*ray;

	// ray = malloc (sizeof(t_raycast));
	x = 0;
	while (x < W_WIDTH)
	{
		ray = malloc (sizeof(t_raycast));
		if (init_ray(data, &ray, x) == 1)
			break;
		side_dist(data, &ray);
		hit_wall(data, &ray);
		calcul_draw_line(data, &ray);
		calcul_view_texture(data, &ray);
		draw_wall(data, &ray, x);
		// draw_line(data, &ray, x);
		free(ray);
		x++;
	}
	// free(ray);
}


void	render(t_data **data)
{
	if ((*data)->index_img == 0 || (*data)->index_img == 3)
	{
		(*data)->img_ptr1 = mlx_new_image((*data)->mlx_ptr, W_WIDTH, W_HEIGHT + 2);
		(*data)->mlx_address = mlx_get_data_addr((*data)->img_ptr1, &(*data)->bite_per_pixel, &(*data)->size_line, &(*data)->endian);
	}
	else
	{
		(*data)->img_ptr2 = mlx_new_image((*data)->mlx_ptr, W_WIDTH, W_HEIGHT + 2);
		(*data)->mlx_address = mlx_get_data_addr((*data)->img_ptr2, &(*data)->bite_per_pixel, &(*data)->size_line, &(*data)->endian);
	}
	// (*data)->mini_map = mlx_new_image((*data)->mlx_ptr, 150, 150);
	// (*data)->mini_data = mlx_get_data_addr((*data)->mini_map, &(*data)->m_bite_per_pixel, &(*data)->m_size_line, &(*data)->m_endian);
	ray_cast(data);
	//mini_map(data);
	if ((*data)->index_img == 0 || (*data)->index_img == 3)
	{
		mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->img_ptr1, 0, 0);
		if ((*data)->index_img == 0)
			mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr2);
		(*data)->index_img = 1;
	}
	else
	{
		mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->img_ptr2, 0, 0);
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr1);
		(*data)->index_img = 0;
	}
	// mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->mini_map, 0, 0);
}


// void	draw_line(t_data **data, t_raycast **ray, int x)
// {
// 	int	y;
// 	int pixel_index;
// 	int	color;

// 	color = 0x00008B;
// 	if ((*ray)->side == 1)
// 		color = color * 2;
// 	y = (*ray)->draw_start;
// 	while (y < (*ray)->draw_end)
// 	{
// 		pixel_index = (y * (*data)->size_line) + (x * ((*data)->bite_per_pixel / 8));
// 		(*data)->mlx_address[pixel_index] = color & 0xFF;
// 		(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
// 		(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
// 		y++;
// 	}
// }