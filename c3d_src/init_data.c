/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:46 by njeanbou          #+#    #+#             */
/*   Updated: 2024/10/03 15:00:53 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"


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

void ft_extrac_map(int fd, char *buffer, t_data **data)
{
    buffer = ft_map_to_buffer(fd, buffer);
	(*data)->map = split_map(buffer, '\n');

	free(buffer);
}

void	calculate_window(t_data **data)
{
	int x;
	int x_tmp;
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
	// printf("%d\n", j);
	(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while (i < (*data)->m_wid + 2)
		(*data)->mapbis[j][i++] = '0';
	(*data)->mapbis[j][i] = '\0';
	j++;
	(*data)->mapbis[j] = NULL;
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

void	extract_color(t_data **data, char **buf)
{
	char	**rgb;
	
	rgb = NULL;
	if (ft_strequal(buf[0], "F") == 0)
	{
		rgb = ft_split(buf[1], ',');
		(*data)->txt_ground = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8) + ft_atoi(rgb[2]);
	}
	else if (ft_strequal(buf[0], "C") == 0)
	{
		rgb = ft_split(buf[1], ',');
		(*data)->txt_ceiling = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8) + ft_atoi(rgb[2]);
	}
	if (rgb != NULL)
		ft_free_tab(rgb);
}

void	extract_texture(t_data **data, char **buf)
{
	if (ft_strequal(buf[0], "NO") == 0)
	{
		(*data)->txt_north = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_north->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		//a faire pour tout avec un exit clean
		if (!(*data)->txt_north->txt_img)
			return ;
		(*data)->txt_north->txt_data = mlx_get_data_addr((*data)->txt_north->txt_img, &(*data)->txt_north->bits_per_pixel, &(*data)->txt_north->size_line, &(*data)->txt_north->endianl);
	}
	else if (ft_strequal(buf[0], "SO") == 0)
	{
		(*data)->txt_south = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_south->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		(*data)->txt_south->txt_data = mlx_get_data_addr((*data)->txt_south->txt_img, &(*data)->txt_south->bits_per_pixel, &(*data)->txt_south->size_line, &(*data)->txt_south->endianl);
	}
	else if (ft_strequal(buf[0], "WE") == 0)
	{
		(*data)->txt_west = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_west->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		(*data)->txt_west->txt_data = mlx_get_data_addr((*data)->txt_west->txt_img, &(*data)->txt_west->bits_per_pixel, &(*data)->txt_west->size_line, &(*data)->txt_west->endianl);
	}
	else if (ft_strequal(buf[0], "EA") == 0)
	{
		(*data)->txt_east = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_east->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		(*data)->txt_east->txt_data = mlx_get_data_addr((*data)->txt_east->txt_img, &(*data)->txt_east->bits_per_pixel, &(*data)->txt_east->size_line, &(*data)->txt_east->endianl);
	}
	else if (ft_strequal(buf[0], "DO") == 0)
	{
		(*data)->txt_door = (t_texture *)malloc (sizeof(t_texture));
		(*data)->txt_door->txt_img = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		(*data)->txt_door->txt_data = mlx_get_data_addr((*data)->txt_door->txt_img, &(*data)->txt_door->bits_per_pixel, &(*data)->txt_door->size_line, &(*data)->txt_door->endianl);
	}
	extract_color(data, buf);
}

void	extract_info(t_data **data, char *av, char *buffer)
{
	int		fd;
	char	**buf;
	
	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Erorr : file does not exist\n", 1);
		exit(1);
	}
	buffer = gnl(fd, buffer);
	buf = ft_split_link(buffer, ' ');		
	while (buffer != NULL && ft_isdigit(first_num(buffer)) != 1)
	{
		// printf("%c\n", first_num(buffer));
		if (buf[0] == NULL)
		{
			buffer = gnl(fd, buffer);
			continue;
		}
		extract_texture(data, buf);
		buffer = gnl(fd, buffer);
		ft_free_tab(buf);
		buf = ft_split_link(buffer, ' ');
	}
	ft_free_tab(buf);
	ft_extrac_map(fd, buffer, data);
}

void	set_dir_bis(t_data **data, char c)
{
	if (c == 'E')
	{
		(*data)->dir_x = 1;
		(*data)->dir_y = 0;
		(*data)->plane_x = 0;
		(*data)->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		(*data)->dir_x = -1;
		(*data)->dir_y = 0;
		(*data)->plane_x = 0;
		(*data)->plane_y = -0.66;
	}
}

void	set_dir(t_data **data, char c)
{
	if (c == 'N')
	{
		(*data)->dir_x = 0;
		(*data)->dir_y = -1;
		(*data)->plane_x = 0.66;
		(*data)->plane_y = 0;
	}
	else if (c == 'S')
	{
		(*data)->dir_x = 0;
		(*data)->dir_y = 1;
		(*data)->plane_x = -0.66;
		(*data)->plane_y = 0;
	}
	set_dir_bis(data, c);
}

void	calculate_pos_player(t_data **data)
{
	int y;
	int	x;

	y = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
		{
			if ((*data)->map[y][x] == 'N' || (*data)->map[y][x] == 'S'
				|| (*data)->map[y][x] == 'E' || (*data)->map[y][x] == 'W')
			{
				(*data)->player_x = (double)x + 0.5;
				(*data)->player_y = (double)y + 0.5;
				set_dir(data, (*data)->map[y][x]);
			}
			x++;
		}
		y++;
	}
}

void	calculate_screen(t_data **data)
{
	Display	*disp;
	Screen	*screen;

	disp = XOpenDisplay(NULL);
	screen = DefaultScreenOfDisplay(disp);
	(*data)->w_wid = screen->width;
	(*data)->W_hei = screen->height;
	XCloseDisplay(disp);
}


void    init_data(char *av, t_data **data, char *buffer)
{
	check_cub(av);
	(*data)->mlx_ptr = mlx_init();
	calculate_screen(data);
	(*data)->win_ptr = mlx_new_window((*data)->mlx_ptr, W_WIDTH, W_HEIGHT, "Cub3d des gros BOOOOWGOS");
	(*data)->index_img = 3;

	(*data)->wid = 500;
	(*data)->hei = 500;
	(*data)->x_mouse = -1;

	// (*data)->player_x = 13;
	// (*data)->player_y = 1.5;
	// (*data)->dir_x = -1;
	// (*data)->dir_y = 0;
	// (*data)->plane_x = 0;
	// (*data)->plane_y = -0.66;

	extract_info(data, av, buffer);
	calculate_window(data);
	calculate_pos_player(data);
	printf("%d, %d\n", (*data)->m_hei, (*data)->m_wid);
	copymap(data);
	// printf("%s\n", (*data)->mapbis[0]);
	// img_test(data);
}

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