/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 02:28:39 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/20 16:50:16 by njeanbou         ###   ########.fr       */
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

void	c_error(char *str, t_data **data)
{
	free_all(data);
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	exit(1);
}

void	c_error_cub(char *str, t_data **data)
{
	free(*data);
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	exit(1);
}
