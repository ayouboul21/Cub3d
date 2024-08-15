/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:47:14 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/15 13:30:45 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mlx_get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	index;

	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return (ft_pixel(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], texture->pixels[index + 3]));
}

void	draw_image(t_map *map, double i, double j, double h_min, double h_max)
{
	int	x;
	int	y;
	int	color = ft_pixel(255, 0, 0, 255);

	x = fmod(map->ray.x_check, map->cell_width) * map->texture->width / map->cell_width;
	// printf("x = %d\n", x);
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
