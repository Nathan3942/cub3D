/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 05:46:04 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/05 08:32:05 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	put_pixel(t_data **data, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = (y * (*data)->mini_size_line) + (x * ((*data)->mini_bite_per_pixel / 8));
	(*data)->mini_addr[pixel_index] = color & 0xFF;
	(*data)->mini_addr[pixel_index + 1] = (color >> 8) & 0xFF;
	(*data)->mini_addr[pixel_index + 2] = (color >> 16) & 0xFF;
}

void    render_cart(t_data **data)
{
    int	x;
	int	y;

	y = 0;
    while (y < ((*data)->m_hei * MINI_MULT))
	{
		
		x = 0;
		while (x < ((*data)->m_wid * MINI_MULT))
		{
			if ((*data)->map[(int)((double)y / MINI_MULT)][(int)((double)x / MINI_MULT)] == '1')
				put_pixel(data, x, y, 0xFFFFFF);
			if ((*data)->map[(int)((double)y / MINI_MULT)][(int)((double)x / MINI_MULT)] == 'D')
				put_pixel(data, x, y, 0x808080);
			x++;
		}
		y++;
	}
}

// void	put_player(t_data **data, int x, int y)
// {
// 	int	color;
// 	int	pixel_index;

// 	color = 0x00FF0000;
// 	pixel_index = (y * (*data)->mini_size_line) + (x * ((*data)->mini_bite_per_pixel / 8));
// 	(*data)->mini_addr[pixel_index] = color & 0xFF;
// 	(*data)->mini_addr[pixel_index + 1] = (color >> 8) & 0xFF;
// 	(*data)->mini_addr[pixel_index + 2] = (color >> 16) & 0xFF;
// }


void	render_player(t_data **data)
{
	int p_x;
	int	p_y;
	int	radius;
	int center_x;
	int center_y;

	radius = MINI_MULT / 2;
	center_x = (int)((*data)->player_x * MINI_MULT);
	center_y = (int)((*data)->player_y * MINI_MULT);

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