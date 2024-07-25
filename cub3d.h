/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 13:32:29 by aoulahra         ###   ########.fr       */
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
int		ft_tablen(char **tab);
int		check_north(int fd, t_map *map);
int		check_south(int fd, t_map *map);
int		check_west(int fd, t_map *map);
int		check_east(int fd, t_map *map);
char	**ft_split_whitespaces(char *str);
void	skip_empty_lines(int fd, t_map *map);

#endif