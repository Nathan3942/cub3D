/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 02:28:39 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/10 17:42:30 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

char	first_num(char *buffer)
{
	int	i;

	if (buffer[0] != ' ')
		return (buffer[0]);
	i = 0;
	while (buffer[i] == ' ')
		i++;
	return (buffer[i]);
}
