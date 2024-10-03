/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 04:31:16 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/03 04:56:36 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void    print_case(t_data **data, int b_y, int b_x, int color)
{
    int y;
    int x;
    int pixel_index;

    y = b_y * 10;
    while (y < (b_y * 10 + 10))
    {
        x = b_x * 10;
        while (x < (b_x * 10 + 10))
        {
            pixel_index = (y * (*data)->m_size_line) + (x * ((*data)->m_bite_per_pixel / 8));
            (*data)->mini_data[pixel_index] = color & 0xFF;
            (*data)->mini_data[pixel_index + 1] = (color >> 8) & 0xFF;
            (*data)->mini_data[pixel_index + 2] = (color >> 16) & 0xFF;
            x++;
        }
        y++;
    }
}

void    print_map(t_data **data)
{
    int y;
    int x;
    int color;

    y = 0;
    while ((*data)->map[y] != NULL)
    {
        x = 0;
        while ((*data)->map[y][x] != '\0')
        {
            if ((*data)->map[y][x] == '1')
                color = 0x66FF00;
            else
                color = 0x000099;
            print_case(data, y, x, color);
            x++;
        }
        y++;
    }
}

void    mini_map(t_data **data)
{
    print_map(data);
}