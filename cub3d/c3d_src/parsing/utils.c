/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 02:28:39 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/19 11:28:22 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

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

void	c_error(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	exit(1);
}
