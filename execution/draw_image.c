/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:47:14 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/15 11:57:13 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mlx_get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	color;
	int	*data;

	data = (int *)texture->pixels;
	color = data[y * texture->width + x];
	return (color);
}

void	draw_image(t_map *map, double i, double j, double h_min, double h_max)
{
	int	x;
	int	y;
	int	color = ft_pixel(255, 0, 0, 255);

	x = fmod(map->ray.x_check, map->texture->width);
	y = (((int)(j - h_min) * map->texture->height)  / (h_max - h_min));
	if (map->ray.rdir == VERTICAL)
	{
		color = mlx_get_pixel(map->texture, x, y);
		if (map->ray.angle <= (3 * M_PI / 2) && map->ray.angle >= (M_PI / 2))
			color = mlx_get_pixel(map->texture, map->texture->width - x -1, y);
	}
	else
	{
		color = mlx_get_pixel(map->texture, x, y);
		if (map->ray.angle >= 0 && map->ray.angle <= M_PI)
			color = mlx_get_pixel(map->texture, map->texture->width - x -1, y);
	}
	mlx_put_pixel(map->mlx.img, i, j, color);
}
