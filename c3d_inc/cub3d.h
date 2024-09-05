/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:24:01 by ichpakov          #+#    #+#             */
/*   Updated: 2024/09/05 14:44:18 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D__
# define __CUB3D__

# include <stdio.h>
# include "../mlx/mlx.h"
# include "../libft/lib_includes/libft.h"
# include "c3d_keys.h"

/*/////////////////////////////////////////////////////////////////////////////
		STRUCTURES TYPEDEFS
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_data
{
	char	*s;
	void	*mlx_ptr;
	void	*win_ptr;

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



#endif