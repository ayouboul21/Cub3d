/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_wall_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:02:40 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/24 23:39:51 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_square_color(t_map *map, uint32_t color, double i, double j)
{
	int	x;
	int	y;

	x = 0;
	map->i = i * 16;
	while (x < 15)
	{
		y = 0;
		map->j = j * 16;
		while (y < 15)
		{
			mlx_put_pixel(map->mlx.img, map->i, map->j, color);
			map->j++;
			y++;
		}
		map->i++;
		x++;
	}
}

void	draw_square(t_map *map, double i, double j)
{
	double	x;
	double	y;

	x = map->player.x - (8 - i) * map->cell_width;
	y = map->player.y - (4 - j) * map->cell_height;
	map->i = i * 16;
	map->j = j * 16;
	if (x < 0 || y < 0 || x / map->cell_width >= map->cols || y / map->cell_height >= map->rows)
		return ;
	else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == '1')
		draw_square_color(map, ft_pixel(0, 0, 0, 255), i, j);
	else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == 'D')
		draw_square_color(map, ft_pixel(255, 0, 0, 255), i, j);
	else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == 'O')
		draw_square_color(map, ft_pixel(0, 255, 0, 255), i, j);
	else if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] != ' ')
		draw_square_color(map, ft_pixel(255, 255, 255, 255), i, j);
	if (map->player.x == x && map->player.y == y)
		draw_square_color(map, ft_pixel(0, 0, 255, 255), i, j);
}

void	draw_mini_map(t_map *map)
{
	double	i;
	double	j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 9)
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
