/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:28:38 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/03 05:08:33 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"


// void	creat_map(t_data **data)
// {
// 	(*data)->hei = 50;
// 	(*data)->wid = 50;
// 	(*data)->img_ptr = mlx_xpm_file_to_image((*data)->mlx_ptr, "../textures/cobel.xpm", &(*data)->wid, &(*data)->hei);
// 	(*data)->img_ptr = mlx_new_image((*data)->mlx_ptr, W_WIDTH, W_HEIGHT);
// 	(*data)->wid = 0;
// 	(*data)->hei = 0;
// 	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->img_ptr, 0, 0);
// }

void	creat_minimap(t_data **data)
{
	int	x;
	int	y;
	
	y = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
		{
			if ((*data)->map[y][x] == '1')
				mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win_ptr, (*data)->txt_north, x * 50, y * 50);

			x++;
		}
		y++;
	}
}
