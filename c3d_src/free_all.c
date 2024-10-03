/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/02 21:12:06 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	free_all(t_data **data)
{
	ft_free_tab((*data)->map);
	ft_free_tab((*data)->mapbis);
	// free((*data)->txt_ceiling);
	// free((*data)->txt_ground);
	free((*data)->txt_north->txt_img);
	free((*data)->txt_north);
	free((*data)->txt_south->txt_img);
	free((*data)->txt_south);
	free((*data)->txt_east->txt_img);
	free((*data)->txt_east);
	free((*data)->txt_west->txt_img);
	free((*data)->txt_west);
	if ((*data)->index_img == 0 || (*data)->index_img == 3)
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr2);
	else
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr1);
	// mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
	free((*data));
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}