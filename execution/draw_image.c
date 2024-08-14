/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:47:14 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/14 15:30:46 by hel-magh         ###   ########.fr       */
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
	int	color;
	int	x;
	int	y;
	
	x = (((int)i % map->cell_width) * map->texture->width /  map->cell_width );
	y = (((int)(j - h_min) * map->texture->height)  / (h_max - h_min));
	color = mlx_get_pixel(map->texture, x, y);
	mlx_put_pixel(map->mlx.img, i, j, color);
}
