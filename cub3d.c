/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:40:05 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/27 16:18:05 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_map map, int status)
{
	if (map.north)
		free(map.north);
	if (map.south)
		free(map.south);
	if (map.west)
		free(map.west);
	if (map.east)
		free(map.east);
	if (map.floor_color)
		free(map.floor_color);
	if (map.ceiling_color)
		free(map.ceiling_color);
	if (map.map)
		free_tab(&map.map);
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
	ft_exit(map, 0);
}
