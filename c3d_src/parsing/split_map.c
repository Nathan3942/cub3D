/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 03:55:15 by njeanbou          #+#    #+#             */
/*   Updated: 2024/11/06 17:06:23 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../c3d_inc/cub3d.h"

int	count_wd(char *buffer, char c)
{
	int	i;
	int	num_wd;

	i = 0;
	num_wd = 0;
	while (buffer[i] != '\0')
	{
		while (buffer[i] != '\0' && buffer[i] == c)
			i++;
		if (buffer[i] != '\0' && buffer[i] != c)
			num_wd++;
		while (buffer[i] != '\0' && buffer[i] != c)
			i++;
	}
	return (num_wd);
}

int	max_map(char *buffer, char sep)
{
	int	i;
	int	max;
	int	tmp;

	i = 0;
	max = 0;
	while (buffer[i] != '\0')
	{
		tmp = 0;
		while (buffer[i] != '\0' && buffer[i] == sep)
			i++;
		while (buffer[i] != '\0' && buffer[i] != sep)
		{
			tmp++;
			i++;
		}
		if (tmp > max)
			max = tmp;
	}
	return (max);
}

char	*put_wd(char *buffer, char c, int *i)
{
	char	*dest;
	int		max;
	int		z;

	while (buffer[*i] != '\0' && buffer[*i] == c)
		(*i)++;
	max = max_map(buffer, c);
	dest = (char *)malloc((max + 1) * sizeof(char));
	z = 0;
	while (buffer[*i] != '\0' && buffer[*i] != c)
	{
		if (buffer[*i] == ' ')
		{
			dest[z++] = '0';
			(*i)++;
		}
		else
			dest[z++] = buffer[(*i)++];
	}
	while (z < max)
		dest[z++] = '0';
	dest[z] = '\0';
	return (dest);
}

char	**split_map(char *buffer, char c)
{
	char	**dest;
	int		num_wd;
	int		i;
	int		pos;

	if (!buffer)
		return (NULL);
	num_wd = count_wd(buffer, c);
	dest = (char **)malloc((num_wd + 1) * sizeof(char *));
	pos = 0;
	i = 0;
	while (i < num_wd)
	{
		dest[i] = put_wd(buffer, c, &pos);
		if (!dest[i])
		{
			while (i >= 0)
				free(dest[i--]);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
