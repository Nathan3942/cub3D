/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:05:37 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/18 16:07:57 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

void	copy_start(t_data **data)
{
	int	i;

	(*data)->mapbis = (char **)malloc(((*data)->m_hei + 3) * sizeof(char *));
	(*data)->mapbis[0] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while ((*data)->map[0][i] != '\0')
		(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i] = '\0';
}

void	copy_end(t_data **data, int i, int j)
{
	(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while (i < (*data)->m_wid + 2)
		(*data)->mapbis[j][i++] = '0';
	(*data)->mapbis[j][i] = '\0';
	j++;
	(*data)->mapbis[j] = NULL;
}

void	copymap(t_data **data)
{
	int	i;
	int	j;

	j = 1;
	copy_start(data);
	while ((*data)->map[j - 1] != NULL)
	{
		i = 1;
		(*data)->mapbis[j] = (char *)malloc
			(((*data)->m_wid + 3) * sizeof(char));
		while ((*data)->map[j - 1][i - 1] != '\0')
		{
			(*data)->mapbis[j][0] = '0';
			(*data)->mapbis[j][i] = (*data)->map[j - 1][i - 1];
			i++;
		}
		(*data)->mapbis[j][i] = '0';
		(*data)->mapbis[j][i + 1] = '\0';
		j++;
	}
	copy_end(data, i, j);
}