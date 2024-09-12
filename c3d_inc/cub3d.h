/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:24:01 by ichpakov          #+#    #+#             */
/*   Updated: 2024/09/12 07:48:36 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../mlx/mlx.h"
#include "../libft/lib_includes/libft.h"
#include "c3d_keys.h"

/*/////////////////////////////////////////////////////////////////////////////
		STRUCTURES TYPEDEFS
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_data
{
	char	*s;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*txt_north;
	char	*txt_south;
	char	*txt_west;
	char	*txt_east;
	char	*txt_ground;
	char	*txt_ceiling;
	char	**map;
	char	**mapbis;
	int		m_wid;
	int		m_hei;
	int		hei;
	int		wid;
	int		w_hei;
	int		w_wei;
	void	*img_ptr;

}	t_data;

/*Notes pour Nathans :
*	J'ai pas pense a d'autres structures donc a toi de voir si
*	si tu trouves quelque chose de pertinant mais je pense
*	qu'on va deja faire une base du jeu en 2d giga epure pour
*	pas se perdre. Mais ajoutes tout ce qui semble bien.
*/

/*/////////////////////////////////////////////////////////////////////////////
		FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

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

#endif