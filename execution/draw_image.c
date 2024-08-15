/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:47:14 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/15 15:39:24 by hel-magh         ###   ########.fr       */
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
	int	color;

	if (map->ray.rdir == VERTICAL)
	{
		if (map->ray.angle <= (3 * M_PI / 2) && map->ray.angle >= (M_PI / 2))
		{
			x = fmod(map->ray.x_check, map->cell_width) * map->texture[0]->width / map->cell_width;
			y = (((int)(j - h_min) * map->texture[0]->height)  / (h_max - h_min));
			color = mlx_get_pixel(map->texture[0], map->texture[0]->width - x -1, y);
		}
		else
		{
			x = fmod(map->ray.x_check, map->cell_width) * map->texture[3]->width / map->cell_width;
			y = (((int)(j - h_min) * map->texture[3]->height)  / (h_max - h_min));
			color = mlx_get_pixel(map->texture[3], x, y);
		}
	}
	else
	{
		if (map->ray.angle >= 0 && map->ray.angle <= M_PI)
		{
			x = fmod(map->ray.x_check, map->cell_width) * map->texture[2]->width / map->cell_width;
			y = (((int)(j - h_min) * map->texture[2]->height)  / (h_max - h_min));
			color = mlx_get_pixel(map->texture[2], map->texture[2]->width - x -1, y);
		}
		else
		{
			x = fmod(map->ray.x_check, map->cell_width) * map->texture[1]->width / map->cell_width;
			y = (((int)(j - h_min) * map->texture[1]->height)  / (h_max - h_min));
			color = mlx_get_pixel(map->texture[1], x, y);
		}
	}
	mlx_put_pixel(map->mlx.img, i, j, color);
}
