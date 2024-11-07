/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 05:46:04 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/07 20:53:07 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	put_pixel(t_data **data, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = (y * (*data)->size_line) + (x * ((*data)->bite_per_pixel / 8));
	(*data)->mlx_address[pixel_index] = color & 0xFF;
	(*data)->mlx_address[pixel_index + 1] = (color >> 8) & 0xFF;
	(*data)->mlx_address[pixel_index + 2] = (color >> 16) & 0xFF;
}

void    render_cart(t_data **data)
{
    int	x;
	int	y;

	y = 10;
    while (y < (((*data)->m_hei * MINI_MULT)) + 10)
	{
		
		x = 10;
		while (x < (((*data)->m_wid * MINI_MULT)) + 10)
		{
			if ((*data)->map[(int)((y - 10) / MINI_MULT)][(int)((x - 10) / MINI_MULT)] == '1')
				put_pixel(data, x, y, 0xFFFFFF);
			else if ((*data)->map[(int)((y - 10) / MINI_MULT)][(int)((x - 10) / MINI_MULT)] == 'D')
				put_pixel(data, x, y, 0x808080);
			else if ((*data)->map[(int)((y - 10) / MINI_MULT)][(int)((x - 10) / MINI_MULT)] == 'C')
				put_pixel(data, x, y, 0xC0C0C0);
			else
				put_pixel(data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	render_player(t_data **data)
{
	int p_x;
	int	p_y;
	int	radius;
	int center_x;
	int center_y;

	radius = MINI_MULT / 2;
	center_x = (int)((*data)->player_x * MINI_MULT) + 10;
	center_y = (int)((*data)->player_y * MINI_MULT) + 10;

	p_y = center_y - radius;
	while (p_y <= center_y + radius)
	{
		p_x = center_x - radius;
		while (p_x <= center_x + radius)
		{
			if ((p_x - center_x) * (p_x - center_x) + (p_y - center_y) * (p_y - center_y) <= radius *radius)
				put_pixel(data, p_x, p_y, 0x00FF0000);
			p_x++;
		}
		p_y++;
	}
}

void    mini_render(t_data **data)
{
    render_cart(data);
	render_player(data);
	render_raycast(data);
}