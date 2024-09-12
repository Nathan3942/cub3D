/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:50:56 by njeanbou          #+#    #+#             */
/*   Updated: 2024/09/12 08:10:17 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	ft_print_map(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("\n\n\n");
	i = 0;
	while (data->mapbis[i])
	{
		printf("%s\n", data->mapbis[i]);
		i++;
	}
}

void	print_txt(t_data *data)
{
	// printf("NO : %s", data->txt_north);
	printf("SO : %s\n", data->txt_south);
	printf("WE : %s\n", data->txt_west);
	printf("EA : %s\n", data->txt_east);
	printf("F : %s\n", data->txt_ground);
	printf("C : %s\n", data->txt_ceiling);
}

void	print_para(t_data *data)
{
	ft_print_map(data);
	print_txt(data);
}