/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/09/16 12:45:23 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	free_all(t_data **data)
{
	ft_free_tab((*data)->map);
	ft_free_tab((*data)->mapbis);
	free((*data)->txt_ceiling);
	free((*data)->txt_ground);
	free((*data)->txt_north);
	free((*data)->txt_south);
	free((*data)->txt_east);
	free((*data)->txt_west);
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