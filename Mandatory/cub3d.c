/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:40:05 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/25 11:02:14 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_map map, int status)
{
	int	i;

	(map.north) && (free(map.north), map.north = NULL);
	(map.south) && (free(map.south), map.north = NULL);
	(map.west) && (free(map.west), map.north = NULL);
	(map.east) && (free(map.east), map.north = NULL);
	(map.floor_color) && (free(map.floor_color), map.north = NULL);
	(map.ceiling_color) && (free(map.ceiling_color), map.north = NULL);
	(map.map) && (free_tab(&map.map), i = -1);
	i = -1;
	while (++i < 4)
		mlx_delete_texture(map.txt[i]);
	if (map.mlx.img)
		mlx_delete_image(map.mlx.mlx, map.mlx.img);
	if (map.mlx.mlx)
		mlx_terminate(map.mlx.mlx);
	exit(status);
}

int	main(int ac, char *av[])
{
	t_map	map;

	ft_bzero(&map, sizeof(t_map));
	if (ac != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		ft_exit(map, 1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		ft_exit(map, 1);
	}
	if (parse(av[1], &map) == -1)
		ft_exit(map, 1);
	render_map(&map);
	ft_exit(map, 0);
}
