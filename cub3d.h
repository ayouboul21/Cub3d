/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 13:20:30 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_map
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	char		*floor;
	char		*ceiling;
	char		**map;
	int			rows;
	int			cols;
}				t_map;

int		parse(char *file, t_map *map);
char	**ft_split_whitespaces(char *str);
int		ft_tablen(char **tab);

#endif