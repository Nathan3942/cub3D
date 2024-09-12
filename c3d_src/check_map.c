/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:55:41 by njeanbou          #+#    #+#             */
/*   Updated: 2024/09/12 10:05:55 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"

void    check_cub(char *av)
{
	int	len;

	len = ft_strlen(av);
	if(len < 5)
	{
		ft_putstr_fd("Error .cub\n", 1);
		exit(1);
	}
	if (av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c' ||
		av[len - 4] != '.')
	{
		ft_putstr_fd("Error .cub\n", 1);
		exit(1);
	}
}

void	check_char(t_data **data)
{
	int	y;
	int	x;

	y = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
		{
			if ((*data)->map[y][x] != '0' && (*data)->map[y][x] != '1' 
				&& (*data)->map[y][x] != 'N' && (*data)->map[y][x] != 'S'
				&& (*data)->map[y][x] != 'E' && (*data)->map[y][x] != 'W'
				&& (*data)->map[y][x] != '\n' && (*data)->map[y][x] != ' ')
			{
				ft_putstr_fd("Error wrong char in map\n", 1);
				exit(1);
			}
			x++;
		}
		y++;
	}
}

bool	check_haud(t_data **data, int *y, int *x)
{
	printf("%d, %d : %c\n", *y, *x, (*data)->map[*y][*x]);
	if ((*data)->map[*y][*x + 1] == '\0')
		return (true);
	if((*data)->map[*y][*x + 1] != '\0' && (*data)->map[*y][*x + 1] == '1')
	{
		(*x)++;
		return (check_haud(data, y, x));
	}
	if((*data)->map[*y + 1] != NULL && (*data)->map[*y + 1][*x] == '1')
	{
		(*y)++;
		return (check_haud(data, y, x));
	}
	if (*y > 0 && (*data)->map[*y - 1][*x] == '1')
	{
		(*y)--;
		return (check_haud(data, y, x));
	}
	if (*x > 0 && (*data)->map[*y][*x - 1] == '1')
	{
		(*x)--;
		return (check_haud(data, y, x));
	}
	return (false);
}

void	print_limit(t_data **data)
{
	int y;
	int	x;

	y = 0;
	while ((*data)->map[y] != NULL)
	{
		x = 0;
		while ((*data)->map[y][x] != '\0')
			x++;
		y++;
	}
	printf("Limit map : y %d, x %d\n", y, x);
}

// char	**copymap(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	**copy_map;

// 	j = 0;
// 	copy_map = (char **)malloc((data->m_hei + 1) * sizeof(char *));
// 	while (data->map[j])
// 	{
// 		i = 0;
// 		copy_map[j] = (char *)malloc ((data->m_wid + 1) * sizeof(char));
// 		while (data->map[j][i])
// 		{
// 			copy_map[j][i] = data->map[j][i];
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (copy_map);
// }

// bool	check_right(t_data **data, int y, int x, int *i)
// {
// 	bool	result;

// 	print_limit(data);
// 	printf("y %d, x %d\n", y, x);
// 	// printf("%d, %d : %c\n", *y, *x, (*data)->map[*y][*x]);
// 	if (*i > 20 && (*data)->mapbis[y][x] == 'F')
// 		return (true);
// 	if (y <= 0 || x <= 0)
//         return (false);
// 	if ((*data)->mapbis[y] == NULL || (*data)->mapbis[y][x] == '\0' || (*data)->mapbis[y][x] != '1')
// 		return (false);
// 	(*i)++;
// 	(*data)->mapbis[y][x] = '0';
// 	result = (check_right(data, y + 1, x, i) || check_right(data, y, x + 1, i)
// 		|| check_right(data, y, x - 1, i) || check_right(data, y - 1, x, i));
// 	return (result);
// }

// char	**copy_map(t_data **data)
// {
// 	int	i;
// 	int	j;
// 	char	**dest;

// 	j = 1;
// 	dest = (char **)malloc(((*data)->m_hei + 2) * sizeof(char *));
// 	dest[0] = (char *)malloc (((*data)->m_wid + 2) * sizeof(char));
// 	i = 0;
// 	while ((*data)->map[0][i] != '\0')
// 		dest[0][i++] = '0';
// 	dest[0][i++] = '0';
// 	dest[0][i] = '\0';
// 	while ((*data)->map[j - 1] != NULL)
// 	{
// 		i = 0;
// 		dest[j] = (char *)malloc (((*data)->m_wid + 2) * sizeof(char));
// 		while ((*data)->map[j - 1][i] != '\0')
// 		{
// 			dest[j][i] = (*data)->map[j - 1][i];
// 			i++;
// 		}
// 		dest[j][i] = '0';
// 		dest[j][i + 1] = '\0';
// 		j++;
// 	}
// 	dest[j] = NULL;
// }

// char	**copymappp(t_data **data)
// {
// 	int	i;
// 	int	j;
// 	char	**mapbis;

// 	j = 0;
// 	mapbis = (char **)malloc(((*data)->m_hei + 1) * sizeof(char *));
// 	while ((*data)->map[j] != NULL)
// 	{
// 		i = 0;
// 		mapbis[j] = (char *)malloc (((*data)->m_wid + 2) * sizeof(char));
// 		while ((*data)->mapbis[j][i] != '\0')
// 		{
// 			mapbis[j][i] = (*data)->mapbis[j][i];
// 			i++;
// 		}
// 		mapbis[j][i] = '\0';
// 		j++;
// 	}
// 	mapbis[j] = NULL;
// 	return (mapbis);
// }

int check_border(char **mapbis, int y, int x, int *i)
{
    int res;

    // Affichage pour débogage
    printf("y %d, x %d, i %d, map %c 		:3\n", y, x, *i, mapbis[y][x]);

    // Vérifiez les limites de la carte et les conditions
    if (*i != 0)
	{
		if (mapbis[y][x] == '2')
			return (0);	
		if (mapbis[y][x] == 'F' && *i > 30)
			return (1);
		if ((y <= 0 || x <= 0 || mapbis[y][x + 1] == '\0'
			|| mapbis[y + 1] == NULL || mapbis[y][x] != '1'))
		{
			printf("y %d, x %d, i %d, map %c :(\n", y, x, *i, mapbis[y][x]);
			return 0;  // Carte non fermée
		}
	}
	(*i)++;
	if (*i == 1 || mapbis[y][x] == '1')
	{
		if (mapbis[y][x] != 'F')
			mapbis[y][x] = '2';
    	res = (check_border(mapbis, y, x + 1, i) || check_border(mapbis, y + 1, x, i)
           || check_border(mapbis, y, x - 1, i) || check_border(mapbis, y - 1, x, i));
		return res;
	}
	return (0);
}

bool	map_close(t_data **data, int *y, int *x, int dep[2])
{
	int		i;

	i = 0;
	(*data)->mapbis[*y][*x] = 'F';
	if (check_border((*data)->mapbis, *y, *x, &i) == 1)
		printf("true\n");
	else
		printf("false\n");
	print_para(*data);
	
}

void	check_close(t_data **data)
{
	int	y;
	int	x;
	int dep[2];

	y = 1;
	x = 1;
	while ((*data)->mapbis[y][x] != '1')
		x++;
	dep[0] = y;
	dep[1] = x;
	if (map_close(data, &y, &x, dep) == false)
	{
		ft_putstr_fd("Error map not close\n", 1);
		exit(1);
	}
}
// if ((*data)->map[y][x] == '1')
	// {
	// 	dep[0] = y;
	// 	dep[1] = x;
	// 	if (map_close(data, &y, &x, dep) == false)
	// 	{
	// 		ft_putstr_fd("Error map not close\n", 1);
	// 		exit(1);
	// 	}
	// }

void    check_map(t_data **data)
{
	check_char(data);
	check_close(data);
}


// int check_border(t_data *data, int y, int x, int *i)
// {
//     int res;

//     // Affichage pour débogage
//     printf("y %d, x %d, i %d\n", y, x, *i);

//     // Vérifiez les limites de la carte et les conditions
//     if (*i != 0)
// 	{
// 		if ((y <= 0 || x < 0 || y >= data->m_hei || x >= data->m_wid
// 			|| data->mapbis[y] == NULL || data->mapbis[y][x] != '1'))
// 		{
// 			printf("%d lala\n", *i);
// 			return 0;  // Carte non fermée
// 		}
// 		if (data->mapbis[y][x] == 'F')
// 			return (1);
// 		// Marquez comme visité
// 		data->mapbis[y][x] = '0';
// 	}
// 	(*i)++;

//     // Vérifiez les voisins
//     res = (check_border(data, y, x + 1, i) || check_border(data, y + 1, x, i)
//            || check_border(data, y, x - 1, i) || check_border(data, y - 1, x, i));
//     return res;
// }

// bool	check_right(t_data **data, int *y, int *x)
// {
// 	bool	result;

// 	print_limit(data);
// 	printf("y %d, x %d\n", *y, *x);
// 	// printf("%d, %d : %c\n", *y, *x, (*data)->map[*y][*x]);
// 	if (*y < 0 || *x < 0 || (*data)->map[*y] == NULL || (*data)->map[*y][*x] == '\0')
//         return (false);
// 	if ((*data)->map[*y + 1] == NULL)
// 		return (true);
// 	if (*y <= 0)
// 		result = (check_right(data, y + 1, x) || check_right(data, y, x + 1)
// 			|| check_right(data, y, x - 1));
// 	else if (*x <= 0)
// 		result = (check_right(data, y + 1, x) || check_right(data, y, x + 1)
// 			|| check_right(data, y - 1, x));
// 	else if ((*data)->map[*y][*x + 1] == '\0')
// 		result = (check_right(data, y + 1, x) || check_right(data, y, x - 1)
// 			|| check_right(data, y - 1, x));
// 	else
// 		result = (check_right(data, y + 1, x) || check_right(data, y, x + 1)
// 			|| check_right(data, y, x - 1) || check_right(data, y - 1, x));
// 	return (result);
// }


// bool	check_right(t_data **data, int *y, int *x)
// {
// 	printf("%d, %d : %c\n", *y, *x, (*data)->map[*y + 1][*x]);
// 	if ((*data)->map[*y + 1] == NULL)
// 		return (true);
// 	if((*data)->map[*y + 1] != NULL && (*data)->map[*y + 1][*x] == '1')
// 	{
// 		(*y)++;
// 		check_right(data, y, x);
// 	}
// 	if((*data)->map[*y][*x + 1] != '\0' && (*data)->map[*y][*x + 1] == '1')
// 	{
// 		(*x)++;
// 		check_right(data, y, x);
// 	}
// 	if (*x > 0 && (*data)->map[*y][*x - 1] == '1')
// 	{
// 		(*x)--;
// 		check_right(data, y, x);
// 	}
// 	if (*y > 0 && (*data)->map[*y - 1][*x] == '1')
// 	{
// 		(*y)--;
// 		check_right(data, y, x);
// 	}
// 	return (false);
// }


// bool	check_haud(t_data **data, int *y, int *x)
// {
// 	while ((*data)->map[*y][*x] != '\0' && (*data)->map[*y][*x + 1] != '\0')
// 	{
// 		printf("%d, %d : %c\n", *y, *x, (*data)->map[*y][*x]);
// 		if ((*data)->map[*y][*x + 1] && (*data)->map[*y][*x + 1] == '1')
// 			(*x)++;
// 		else if ((*data)->map[*y + 1] && (*data)->map[*y + 1][*x] == '1')
// 			(*y)++;
// 		else if (*y > 0 && (*data)->map[*y - 1][*x] == '1')
// 			(*y)--;
// 		else
// 			return (false);
// 	}
// 	return (true);
// }



// bool	map_close(t_data **data, int *y, int *x, int dep[2])
// {
// 	printf("%d %d : %c , %c\n", *y, *x, (*data)->map[*y][*x], (*data)->map[*y][*x + 1]);
// 	if (*y == dep[0] - 1 && *x == dep[1])
//         return (true);
//     if ((*data)->map[*y][*x + 1] != '\0' && (*data)->map[*y][*x + 1] == '1')
// 	{
// 		printf("droite\n");
// 		(*x)++;
//         return map_close(data, y, x, dep);
// 	}
// 	else if ((*data)->map[*y - 1][*x] && (*data)->map[*y - 1][*x] == '1')
//     {
// 		printf("bas\n");
// 		(*y)--;
// 	    return map_close(data, y, x, dep);
// 	}
// 	else if ((*data)->map[*y][*x - 1] && (*data)->map[*y][*x - 1] == '1')
//     {
// 		printf("gauche\n");
// 		(*x)--;
// 	    return map_close(data, y, x, dep);
// 	}
// 	else if ((*data)->map[*y + 1][*x] && (*data)->map[*y + 1][*x] == '1')
//     {
// 		printf("haud\n");
// 		(*y)++;
// 	    return map_close(data, y, x, dep);
// 	}
// 	return (false);
// }
