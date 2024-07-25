/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:40:05 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 14:35:22 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
    atexit(f);
	t_map	map;

	if (ac != 2)
	{
		write(2, "Error invalid number of arguments\n", 35);
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error invalid file extension\n", 30);
		return (1);
	}
	if (parse(av[1], &map) == -1)
	{
		write(2, "Error invalid file\n", 19);
		return (1);
	}
}
