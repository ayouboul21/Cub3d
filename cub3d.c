/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:40:05 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 10:55:29 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	if (ac != 2)
	{
		write(2, "Error invalid number of arguments\n", 34);
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error invalid file extension\n", 29);
		return (1);
	}
	if (parse(av[1]) == -1)
	{
		write(2, "Error invalid file\n");
		return (1);
	}
}
