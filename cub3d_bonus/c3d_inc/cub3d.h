/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:24:01 by ichpakov          #+#    #+#             */
/*   Updated: 2024/11/20 17:36:43 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/lib_includes/libft.h"
# include "c3d_keys.h"

/*/////////////////////////////////////////////////////////////////////////////
		STRUCTURES TYPEDEFS
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_texture
{
	void	*txt_img;
	int		bits_per_pixel;
	int		size_line;
	int		endianl;
	char	*txt_data;

}	t_texture;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			*mlx_address;

	t_texture		*txt_north;
	t_texture		*txt_south;
	t_texture		*txt_west;
	t_texture		*txt_east;
	t_texture		*txt_door;
	unsigned int	txt_ground;
	unsigned int	txt_ceiling;

	char			**map;
	char			**mapbis;
	int				m_wid;
	int				m_hei;

	int				hei;
	int				wid;
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

	void			*img_ptr1;
	void			*img_ptr2;
	int				bite_per_pixel;
	int				size_line;
	int				endian;
	int				index_img;

	int				m_mult;
	bool			m_left;
	bool			m_right;
	bool			m_up;
	bool			m_down;
	bool			t_left;
	bool			t_right;
	int				x_mouse;

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

/*/////////////////////////////////////////////////////////////////////////////
		FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

//render
void	render(t_data **data);
void	draw_wall(t_data **data, t_raycast **ray, int x);
void	calcul_draw_line(t_data **data, t_raycast **ray);
void	calcul_view_texture(t_data **data, t_raycast **ray);
int		init_ray(t_data **data, t_raycast **ray, int x);
void	side_dist(t_data **data, t_raycast **ray);
void	hit_wall(t_data **data, t_raycast **ray);

//init
char	*gnl(int fd, char *buffer);
char	*gnl_map(int fd, char *buffer);
void	init_data(char *av, t_data **data, char *buffer);
void	creat_map(t_data **data);
char	**split_map(char *buffer, char c);
void	calculate_pos_player(t_data **data);
void	ft_extrac_map(int fd, char *buffer, t_data **data);
void	extract_info(t_data **data, char *av, char *buffer);
void	extract_texture(t_data **data, char **buf, int (*nb_txt)[2]);
void	extract_north(t_data **data, char **buf, int (*nb_txt)[2]);
void	extract_south(t_data **data, char **buf, int (*nb_txt)[2]);
void	extract_east(t_data **data, char **buf, int (*nb_txt)[2]);
void	extract_west(t_data **data, char **buf, int (*nb_txt)[2]);
void	extract_door(t_data **data, char **buf, int (*nb_txt)[2]);
void	extract_color(t_data **data, char **buf, int (*nb_txt)[2]);
void	copymap(t_data **data);

//move
void	input(t_data **data);
void	move(t_data **data);
void	move_lat(t_data **data);
int		mouse_move(int x, int y, t_data **data);
void	door(t_data **data);

//mini map
void	mini_render(t_data **data);
void	render_raycast(t_data **data);

//free
void	ft_free_tab(char **tab);
void	free_all(t_data **data);
void	error(char *str);

//utils
char	first_num(char *buffer);
void	c_error(char *str, t_data **data);
void	c_error_cub(char *str, t_data **data);

//check_map
void	check_cub(char *av, t_data **data);
void	check_map(t_data **data);
void	check_close(t_data **data);


#endif