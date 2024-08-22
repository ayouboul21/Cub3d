/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_wall_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:02:40 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/22 17:04:04 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_square(t_map *map, double i, double j)
{
	double	x;
	double	y;

	x = map->player.x - (8 - i) * map->cell_width;
	i *= map->cell_width / 5;
	while (x / map->cell_width < floor(x / map->cell_width) + 1)
	{
		y = map->player.y - (5 - j) * map->cell_height;
		j *= map->cell_height / 5;
		while (y / map->cell_height < floor(y / map->cell_height) + 1)
		{
			if (y < 0 || x < 0 || y >= map->mlx.height || x >= map->mlx.width)
			{
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(0, 0, 0, 0));
				y += 5;
				j++;
				continue ;
			}
			if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == '1')
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(255, 255, 255, 255));
			else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == '0')
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(0, 255, 0, 255));
			else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == 'D')
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(255, 0, 0, 255));
			else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == 'O')
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(0, 0, 255, 255));
			y += 5;
			j++;
		}
		x += 5;
		i++;
	}
}

void	draw_mini_map(t_map *map)
{
	double	i;
	double	j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 10)
		{
			draw_square(map, i, j);
			j++;
		}
		i++;
	}
}

int	distance_to_wall(t_map *map, double x, double y, double angle)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.x = x;
	ray.y = y;
	map->player.angle = map->player.angle - angle;
	if (map->player.angle < 0)
		while (map->player.angle < 0)
			map->player.angle += 360;
	else if (map->player.angle >= 360)
		while (map->player.angle >= 360)
			map->player.angle -= 360;
	ray.angle = map->player.angle * M_PI / 180;
	get_ray_distance(map, &ray);
	map->player.angle = map->player.angle + angle;
	if (map->player.angle < 0)
		while (map->player.angle < 0)
			map->player.angle += 360;
	else if (map->player.angle >= 360)
		while (map->player.angle >= 360)
			map->player.angle -= 360;
	if (fabs(ray.distance) < map->epsilon)
		return (0);
	return (1);
}
