/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 15:52:21 by aoulahra         ###   ########.fr       */
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
# include "libft/libft.h"
# include "MLX42/MLX42.h"

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}		t_color;

typedef struct s_map
{
	int		rows;
	int		cols;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
	char	*sprite;
    char	*floor_color;
    char	*ceiling_color;
	t_color	floor;
	t_color	ceiling;
}				t_map;

int		parse(char *file, t_map *map);
int		ft_tablen(char **tab);
int		check_north(int fd, t_map *map);
int		check_south(int fd, t_map *map);
int		check_west(int fd, t_map *map);
int		check_east(int fd, t_map *map);
int		check_ceiling_color(int fd, t_map *map);
int		check_floor_color(int fd, t_map *map);
char	**ft_split_whitespaces(char *str);
void	skip_empty_lines(int fd, t_map *map, char mode);

#endif