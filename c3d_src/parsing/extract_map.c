/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:08:54 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/06 17:06:00 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

char	*ft_map_to_buffer(int fd, char *buffer)
{
	char	*buff;
	char	*tmp;

	if (buffer == NULL)
		return (NULL);
	buff = ft_strdup(buffer);
	while (buffer != NULL)
	{
		buffer = gnl(fd, buffer);
		if (buffer != NULL)
		{
			tmp = buff;
			buff = ft_strjoin(buff, buffer);
			free(tmp);
		}
	}
	return (buff);
}

void	ft_extrac_map(int fd, char *buffer, t_data **data)
{
	buffer = ft_map_to_buffer(fd, buffer);
	(*data)->map = split_map(buffer, '\n');
	free(buffer);
}
