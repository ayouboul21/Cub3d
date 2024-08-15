/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:47:14 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/15 09:58:03 by aoulahra         ###   ########.fr       */
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
	int	color;

	x = fmod(map->ray.x_check, map->texture->width);
	y = (((int)(j - h_min) * map->texture->height)  / (h_max - h_min));
	color = mlx_get_pixel(map->texture, x, y);
	mlx_put_pixel(map->mlx.img, i, j, color);
}
