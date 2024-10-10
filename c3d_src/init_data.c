/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:46 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/10 17:44:53 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void	calculate_window(t_data **data)
{
	int	x;
	int	x_tmp;
	int	y;

	y = 0;
	x_tmp = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
			x++;
		if (x > x_tmp)
			x_tmp = x;
		y++;
	}
	(*data)->m_wid = x_tmp;
	(*data)->m_hei = y;
}

void	copymap(t_data **data)
{
	int	i;
	int	j;

	j = 1;
	(*data)->mapbis = (char **)malloc(((*data)->m_hei + 3) * sizeof(char *));
	(*data)->mapbis[0] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while ((*data)->map[0][i] != '\0')
		(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i++] = '0';
	(*data)->mapbis[0][i] = '\0';
	while ((*data)->map[j - 1] != NULL)
	{
		i = 1;
		(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
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
	(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while (i < (*data)->m_wid + 2)
		(*data)->mapbis[j][i++] = '0';
	(*data)->mapbis[j][i] = '\0';
	j++;
	(*data)->mapbis[j] = NULL;
}

void	init_data(char *av, t_data **data, char *buffer)
{
	check_cub(av);
	(*data)->mlx_ptr = mlx_init();
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr, W_WIDTH, W_HEIGHT,
			"Cub3d des gros BOOOOWGOS");
	(*data)->index_img = 3;

	(*data)->wid = 500;
	(*data)->hei = 500;
	(*data)->x_mouse = -1;

	(*data)->m_up = false;
	(*data)->m_down = false;
	(*data)->m_left = false;
	(*data)->m_right = false;
	(*data)->t_left = false;
	(*data)->t_right = false;

	extract_info(data, av, buffer);
	calculate_window(data);
	calculate_pos_player(data);
	copymap(data);
}



// void	set_info_texture(t_data **data)
// {
// 	(*data)->txt_north.witdh = 50;
// 	(*data)->txt_north.height = 50;

// 	(*data)->txt_south.witdh = 50;
// 	(*data)->txt_south.height = 50;

// 	(*data)->txt_east.witdh = 50;
// 	(*data)->txt_east.height = 50;

// 	(*data)->txt_west.witdh = 50;
// 	(*data)->txt_west.height = 50;
// }


// void	calculate_screen(t_data **data)
// {
// 	Display	*disp;
// 	Screen	*screen;

// 	disp = XOpenDisplay(NULL);
// 	screen = DefaultScreenOfDisplay(disp);
// 	(*data)->w_wid = screen->width;
// 	(*data)->W_hei = screen->height;
// 	XCloseDisplay(disp);
// }

//printf("%s\n", buf[1][1]);
		// 	if (ft_strequal(buf[1][0], "NO") == 0)
		// 	(*data)->txt_north = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1][1], (*data)->wid, (*data)->hei);
		// else if (ft_strequal(buf[1][0], "SO") == 0)
		// 	(*data)->txt_north = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1][1], (*data)->wid, (*data)->hei);
		// else if (ft_strequal(buf[1][0], "WE") == 0)
		// 	(*data)->txt_north = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1][1], (*data)->wid, (*data)->hei);
		// else if (ft_strequal(buf[1][0], "EA") == 0)
		// 	(*data)->txt_north = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1][1], (*data)->wid, (*data)->hei);
		



	// while (buffer != NULL && buffer[0] != '1')
	// {
	// 	// if (ft_strequal(buf[1][0], "NO") == 0)
	// 	// 	data->txt_north = mlx_xpm_file_to_image(data->mlx_ptr, buf[1][1], &data->xpm_wid, &data->xpm_hei);
	// 	// else if (ft_strequal(buf[1][0], "SO") == 0)
	// 	// 	data->txt_north = mlx_xpm_file_to_image(data->mlx_ptr, buf[1][1], &data->xpm_wid, &data->xpm_hei);
	// 	// else if (ft_strequal(buf[1][0], "WE") == 0)
	// 	// 	data->txt_north = mlx_xpm_file_to_image(data->mlx_ptr, buf[1][1], &data->xpm_wid, &data->xpm_hei);
	// 	// else if (ft_strequal(buf[1][0], "EA") == 0)
	// 	// 	data->txt_north = mlx_xpm_file_to_image(data->mlx_ptr, buf[1][1], &data->xpm_wid, &data->xpm_hei);
	// 	ft_free(buf[1]);
	// 	buffer = gnl(fd, buffer);
	// 	printf("%s\n", buffer);
	// 	buf[1] = ft_split(buffer, ' ');
	// 	printf("%s, %s\n", buf[1][0], buf[1][1]);
	// 	//rgb
	// 	// else if (ft_strequal(buf[1][0], "F") == 0)
	// 	// 	data->txt_north = mlx_xpm_file_to_image(data->mlx_ptr, buf[1][1], &data->xpm_wid, &data->xpm_hei);
	// 	// else if (ft_strequal(buf[1][0], "C") == 0)
	// 	// 	data->txt_north = mlx_xpm_file_to_image(data->mlx_ptr, buf[1][1], &data->xpm_wid, &data->xpm_hei);
	// }


	// void	copymap(t_data **data)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	(*data)->mapbis = (char **)malloc(((*data)->m_hei + 1) * sizeof(char *));
// 	while ((*data)->map[j] != NULL)
// 	{
// 		i = 0;
// 		(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 2) * sizeof(char));
// 		while ((*data)->map[j][i] != '\0')
// 		{
// 			(*data)->mapbis[j][i] = (*data)->map[j][i];
// 			i++;
// 		}
// 		(*data)->mapbis[j][i] = '\0';
// 		j++;
// 	}
// 	(*data)->mapbis[j] = NULL;
// }