/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:05:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/05 09:29:22 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	ray_cast(t_data **data)
{
	int			x;
	t_raycast	*ray;

	x = 0;
	while (x < W_WIDTH)
	{
		ray = malloc (sizeof(t_raycast));
		if (init_ray(data, &ray, x) == 1)
			break ;
		side_dist(data, &ray);
		hit_wall(data, &ray);
		calcul_draw_line(data, &ray);
		calcul_view_texture(data, &ray);
		draw_wall(data, &ray, x);
		free(ray);
		x++;
	}
}

void	setup_img(t_data **data)
{
	if ((*data)->index_img == 0 || (*data)->index_img == 3)
	{
		(*data)->img_ptr1 = mlx_new_image((*data)->mlx_ptr,
				W_WIDTH, W_HEIGHT + 2);
		(*data)->mlx_address = mlx_get_data_addr((*data)->img_ptr1,
				&(*data)->bite_per_pixel, &(*data)->size_line,
				&(*data)->endian);
		(*data)->mini_img1 = mlx_new_image((*data)->mlx_ptr, (*data)->m_wid * MINI_MULT, (*data)->m_hei * MINI_MULT);
		(*data)->mini_addr = mlx_get_data_addr((*data)->mini_img1, &(*data)->mini_bite_per_pixel, &(*data)->mini_size_line, &(*data)->mini_endian);
	}
	else
	{
		(*data)->img_ptr2 = mlx_new_image((*data)->mlx_ptr,
				W_WIDTH, W_HEIGHT + 2);
		(*data)->mlx_address = mlx_get_data_addr((*data)->img_ptr2,
				&(*data)->bite_per_pixel, &(*data)->size_line,
				&(*data)->endian);
		(*data)->mini_img2 = mlx_new_image((*data)->mlx_ptr, (*data)->m_wid * MINI_MULT, (*data)->m_hei * MINI_MULT);
		(*data)->mini_addr = mlx_get_data_addr((*data)->mini_img2, &(*data)->mini_bite_per_pixel, &(*data)->mini_size_line, &(*data)->mini_endian);
	}
}

void	render(t_data **data)
{
	input(data);
	setup_img(data);
	mini_render(data);
	ray_cast(data);
	if ((*data)->index_img == 0 || (*data)->index_img == 3)
	{
		mlx_put_image_to_window((*data)->mlx_ptr,
			(*data)->win_ptr, (*data)->img_ptr1, 0, 0);
		mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->mini_img1, 10, 10);
		if ((*data)->index_img == 0)
		{
			mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr2);
			mlx_destroy_image((*data)->mlx_ptr, (*data)->mini_img2);
		}
		(*data)->index_img = 1;
	}
	else
	{
		mlx_put_image_to_window((*data)->mlx_ptr,
			(*data)->win_ptr, (*data)->img_ptr2, 0, 0);
		mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->mini_img2, 10, 10);
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr1);
		mlx_destroy_image((*data)->mlx_ptr, (*data)->mini_img1);
		(*data)->index_img = 0;
	}
}
