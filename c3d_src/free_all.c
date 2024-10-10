/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/10 16:46:38 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	free_all(t_data **data)
{
	if ((*data)->map)
		ft_free_tab((*data)->map);
	if ((*data)->mapbis)
		ft_free_tab((*data)->mapbis);
	if ((*data)->txt_north)
	{
		mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_north->txt_img);
		free((*data)->txt_north);
	}
	if ((*data)->txt_south)
	{
		mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_south->txt_img);
		free((*data)->txt_south);
	}
	if ((*data)->txt_east)
	{
		mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_east->txt_img);
		free((*data)->txt_east);
	}
	if ((*data)->txt_west)
	{
		mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_west->txt_img);
		free((*data)->txt_west);
	}
	if ((*data)->txt_door)
	{
		mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_door->txt_img);
		free((*data)->txt_door);
	}
	if (((*data)->index_img == 0 || (*data)->index_img == 3)
		&& (*data)->img_ptr2)
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr2);
	else
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr1);
	free((*data));
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL || tab[0] == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
