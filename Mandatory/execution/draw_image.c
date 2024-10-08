/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:47:14 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/19 17:15:26 by aoulahra         ###   ########.fr       */
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

void	draw_horizantal(t_map *map, double j)
{
	int	x;
	int	y;

	if (map->ray.angle >= 0 && map->ray.angle <= M_PI)
	{
		x = fmod(map->ray.x_check, map->cell_width)
			* map->txt[2]->width / map->cell_width;
		y = (((int)(j - map->h_min) * map->txt[2]->height)
				/ (map->h_max - map->h_min));
		map->clr = mlx_get_pixel(map->txt[2], map->txt[2]->width - x - 1, y);
	}
	else
	{
		x = fmod(map->ray.x_check, map->cell_width)
			* map->txt[1]->width / map->cell_width;
		y = (((int)(j - map->h_min) * map->txt[1]->height)
				/ (map->h_max - map->h_min));
		map->clr = mlx_get_pixel(map->txt[1], x, y);
	}
}

void	draw_image(t_map *map, double i, double j)
{
	int	x;
	int	y;

	if (map->ray.rdir == VERTICAL)
	{
		if (map->ray.angle <= (3 * M_PI / 2) && map->ray.angle >= (M_PI / 2))
		{
			x = fmod(map->ray.x_check, map->cell_width)
				* map->txt[0]->width / map->cell_width;
			y = (((int)(j - map->h_min) * map->txt[0]->height)
					/ (map->h_max - map->h_min));
			map->clr = mlx_get_pixel(map->txt[0], map->txt[0]->width - x -1, y);
		}
		else
		{
			x = fmod(map->ray.x_check, map->cell_width) * map->txt[3]->width
				/ map->cell_width;
			y = (((int)(j - map->h_min) * map->txt[3]->height)
					/ (map->h_max - map->h_min));
			map->clr = mlx_get_pixel(map->txt[3], x, y);
		}
	}
	else
		draw_horizantal(map, j);
	mlx_put_pixel(map->mlx.img, i, j, map->clr);
}

void	draw_wall(t_map *map, t_ray ray, double i)
{
	double	j;
	double	wall_height;

	j = 0;
	map->ray = ray;
	wall_height = (map->mlx.height / ray.distance) * map->player.wall_height;
	map->h_min = (map->mlx.height / 2) - (wall_height / 2);
	map->h_max = map->h_min + wall_height;
	while ((int)j < map->mlx.height)
	{
		if (j <= map->h_min)
			mlx_put_pixel(map->mlx.img, i, j, ft_pixel(map->ceiling.red,
					map->ceiling.green, map->ceiling.blue, 255));
		else if (j > map->h_min && j < map->h_max)
			draw_image(map, i, j);
		else
			mlx_put_pixel(map->mlx.img, i, j, ft_pixel(map->floor.red,
					map->floor.green, map->floor.blue, 255));
		j++;
	}
}
