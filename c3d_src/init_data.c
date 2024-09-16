/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:46 by njeanbou          #+#    #+#             */
/*   Updated: 2024/09/16 15:05:29 by njeanbou         ###   ########.fr       */
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
	(*data)->w_hei = y * U_HEIGHT;
	(*data)->w_wei = x_tmp * U_WIDTH;
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
	printf("%d\n", j);
	(*data)->mapbis[j] = (char *)malloc (((*data)->m_wid + 3) * sizeof(char));
	i = 0;
	while (i < (*data)->m_wid + 2)
		(*data)->mapbis[j][i++] = '0';
	(*data)->mapbis[j][i] = '\0';
	j++;
	(*data)->mapbis[j] = NULL;
}

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


void    init_data(char *av, t_data **data, char *buffer)
{
	char	**buf;
	int 	fd;

	check_cub(av);
	(*data)->wid = 50;
	(*data)->hei = 50;
	(*data)->mlx_ptr = mlx_init();
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
		printf("%c\n", first_num(buffer));
		if (buf[0] == NULL)
		{
			buffer = gnl(fd, buffer);
			continue;
		}
		if (ft_strequal(buf[0], "NO") == 0)
			(*data)->txt_north = mlx_xpm_file_to_image((*data)->mlx_ptr, buf[1], &(*data)->wid, &(*data)->hei);
		else if (ft_strequal(buf[0], "SO") == 0)
			(*data)->txt_south = ft_strdup(buf[1]);
		else if (ft_strequal(buf[0], "WE") == 0)
			(*data)->txt_west = ft_strdup(buf[1]);
		else if (ft_strequal(buf[0], "EA") == 0)
			(*data)->txt_east = ft_strdup(buf[1]);
		else if (ft_strequal(buf[0], "F") == 0)
			(*data)->txt_ground = ft_strdup(buf[1]);
		else if (ft_strequal(buf[0], "C") == 0)
			(*data)->txt_ceiling = ft_strdup(buf[1]);
		buffer = gnl(fd, buffer);
		ft_free_tab(buf);
		buf = ft_split_link(buffer, ' ');
	}
	ft_free_tab(buf);
	ft_extrac_map(fd, buffer, data);
	calculate_window(data);
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