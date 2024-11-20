/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/20 17:27:54 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	error(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

void	free_other(t_data **data)
{
	if ((*data)->txt_east != NULL)
	{
		if ((*data)->txt_east->txt_img)
			mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_east->txt_img);
		free((*data)->txt_east);
	}
	if ((*data)->txt_west != NULL)
	{
		if ((*data)->txt_west->txt_img)
			mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_west->txt_img);
		free((*data)->txt_west);
	}
}

void	free_img(t_data **data)
{
	if ((*data)->index_img == 3)
		return ;
	if (((*data)->index_img == 0) && (*data)->img_ptr2)
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr2);
	else
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img_ptr1);
}

void	free_all(t_data **data)
{
	if ((*data)->map != NULL)
		ft_free_tab((*data)->map);
	if ((*data)->mapbis != NULL)
		ft_free_tab((*data)->mapbis);
	if ((*data)->txt_north != NULL)
	{
		if ((*data)->txt_north->txt_img)
			mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_north->txt_img);
		free((*data)->txt_north);
	}
	if ((*data)->txt_south != NULL)
	{
		if ((*data)->txt_south->txt_img)
			mlx_destroy_image((*data)->mlx_ptr, (*data)->txt_south->txt_img);
		free((*data)->txt_south);
	}
	free_other(data);
	free_img(data);
	mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
	mlx_destroy_display((*data)->mlx_ptr);
	free((*data)->mlx_ptr);
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
