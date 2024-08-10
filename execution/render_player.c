/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:33:56 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/10 12:10:26 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_vertices(t_map *map, float h_width, float h_height, int *v)
{
	float		angle;
	t_player	player;

	player = map->player;
	angle = map->player.angle * M_PI / 180.0;
	v[0] = player.x + (player.x - player.x) * cos(angle)
		- (player.y - h_height - player.y) * sin(angle);
	v[1] = player.y + (player.x - player.x) * sin(angle)
		+ (player.y - h_height - player.y) * cos(angle);
	v[2] = player.x + (player.x - h_width - player.x)
		* cos(angle) - (player.y + h_height - player.y) * sin(angle);
	v[3] = player.y + (player.x - h_width - player.x)
		* sin(angle) + (player.y + h_height - player.y) * cos(angle);
	v[4] = player.x + (player.x + h_width - player.x)
		* cos(angle) - (player.y + h_height - player.y) * sin(angle);
	v[5] = player.y + (player.x + h_width - player.x)
		* sin(angle) + (player.y + h_height - player.y) * cos(angle);
}

int	is_inside_triangle(int i, int j, int *v)
{
	float	alpha;
	float	beta;
	float	denominator;

	denominator = (float)((v[3] - v[5])
			* (v[0] - v[4]) + (v[4] - v[2]) * (v[1] - v[5]));
	alpha = ((float)((v[3] - v[5]) * (i - v[4])
				+ (v[4] - v[2]) * (j - v[5]))) / denominator;
	beta = ((float)((v[5] - v[1]) * (i - v[4])
				+ (v[0] - v[4]) * (j - v[5]))) / denominator;
	return (alpha >= 0 && beta >= 0 && 1 - alpha - beta >= 0);
}

void	draw_player(t_map *map)
{
	int	v[6];
	int	i;
	int	j;

	calculate_vertices(map, map->cell_width / 4, map->cell_height / 4, v);
	i = map->player.x - map->cell_width / 4;
	while (++i < map->mlx.width)
	{
		j = map->player.y - map->cell_height / 4;
		while (++j < map->mlx.height)
			if (is_inside_triangle(i, j, v))
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(0, 255, 0, 255));
	}
	cast_rays(map);
}
