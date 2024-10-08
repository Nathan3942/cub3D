/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:24:01 by ichpakov          #+#    #+#             */
/*   Updated: 2024/10/08 16:01:27 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include "../mlx/mlx.h"
#include "../libft/lib_includes/libft.h"
#include "c3d_keys.h"
#include <X11/Xlib.h>

/*/////////////////////////////////////////////////////////////////////////////
		STRUCTURES TYPEDEFS
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_texture
{
	void	*txt_img;
	// int		witdh;
	// int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endianl;
	char	*txt_data;

}	t_texture;

typedef struct s_data
{
	//mlx
	void	*mlx_ptr;
	void	*win_ptr;
	char	*mlx_address;
	//texture
	t_texture	*txt_north;
	t_texture	*txt_south;
	t_texture	*txt_west;
	t_texture	*txt_east;
	t_texture	*txt_door;
	unsigned int	txt_ground;
	unsigned int	txt_ceiling;
	//minimap
	void	*mini_map;
	char	*mini_data;
	int		mini_w;
	int		mini_h;
	int		m_bite_per_pixel;
	int		m_size_line;
	int		m_endian;

	//map
	char	**map;
	char	**mapbis;
	int		m_wid;
	int		m_hei;
	//state
	int		W_hei;
	int		w_wid;
	int		hei;
	int		wid;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	//image
	void	*img_ptr1;
	void	*img_ptr2;
	int		bite_per_pixel;
	int		size_line;
	int		endian;
	int		index_img;

	//input
	bool	m_left;
	bool	m_right;
	bool	m_up;
	bool	m_down;
	bool	t_left;
	bool	t_right;
	int		x_mouse;

}	t_data;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	unit_dir_x;
	double	unit_dir_y;
	int		step_x;
	int		step_y;
	double	ray_pos_x;
	double	ray_pos_y;
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	
}	t_raycast;


/*Notes pour Nathans :
*	J'ai pas pense a d'autres structures donc a toi de voir si
*	si tu trouves quelque chose de pertinant mais je pense
*	qu'on va deja faire une base du jeu en 2d giga epure pour
*	pas se perdre. Mais ajoutes tout ce qui semble bien.
*/

/*/////////////////////////////////////////////////////////////////////////////
		FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

//render
void	render(t_data **data);
void	draw_wall(t_data **data, t_raycast **ray, int x);

//init
char	*gnl(int fd, char *buffer);
char	*gnl_map(int fd, char *buffer);
void    init_data(char *av, t_data **data, char *buffer);
void	creat_map(t_data **data);
char    **split_map(char *buffer, char c);

// test
void	print_para(t_data *data);

//free
void	ft_free_tab(char **tab);
void	free_all(t_data **data);

//utils
char	first_num(char *buffer);

//check_map
void    check_cub(char *av);
void    check_map(t_data **data);

//mini_map
void    mini_map(t_data **data);

//input
void	input(t_data **data);

#endif