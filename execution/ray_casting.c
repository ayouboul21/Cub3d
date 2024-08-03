/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:32:53 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/03 14:23:18 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_rays(t_map *map)
{
	double	i;

	i = 0;
	map->player.ray_angle = map->player.angle + map->fov / 2;
	while (i < map->fov)
	{
		map->player.ray_angle = map->player.ray_angle
			- map->fov / map->ray_count;
		cast_ray(map);
		i += map->fov / map->ray_count;
	}
    mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}

double	get_horizontal_distance(t_map *map, t_ray ray)
{
	double	x;
	double	y;

	x = ray.x;
	y = ray.y;
	if (cos(ray.angle) >= 0)
		x = floor((x / map->cell_width)) * map->cell_width + map->cell_width + 0.0001;
	else
		x = floor((x / map->cell_width)) * map->cell_width - 0.0001;
	y += (x - ray.x) * tan(ray.angle);
	while (1)
	{
        if (floor((y / map->cell_height)) >= map->rows && floor((x / map->cell_width)) >= map->cols
            && floor(y / map->cell_height) < 0 && floor(x / map->cell_width) < 0)
            break ;
        if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == '1')
            break ;
		y += map->cell_width * tan(ray.angle);
		x += map->cell_width;
	}
	return (sqrt(pow(ray.x - x, 2) + pow(ray.y - y, 2)));
}

double	get_vertical_distance(t_map *map, t_ray ray)
{
	double	x;
	double	y;

	x = ray.x;
	y = ray.y;
	if (sin(ray.angle) >= 0)
		y = floor((y / map->cell_height)) * map->cell_height + map->cell_height + 0.0001;
	else
		y = floor((y / map->cell_height)) * map->cell_height - 0.0001;
	x += (y - ray.y) / tan(ray.angle);
	while (1)
	{
        if (floor((y / map->cell_height)) >= map->rows && floor((x / map->cell_width)) >= map->cols
            && floor(y / map->cell_height) < 0 && floor(x / map->cell_width) < 0)
            break ;
        if (map->map[(int)(y / map->cell_height)][(int)(x / map->cell_width)] == '1')
            break ;
		x += map->cell_height / tan(ray.angle);
		y += map->cell_height;
	}
	return (sqrt(pow(ray.x - x, 2) + pow(ray.y - y, 2)));
}

void	get_ray_distance(t_map *map, t_ray *ray)
{
	double	hor_distance;
	double	ver_distance;

	hor_distance = get_horizontal_distance(map, *ray);
	ver_distance = get_vertical_distance(map, *ray);
	ray->distance = fmin(hor_distance, ver_distance);
}

void    draw_line(t_map *map, t_ray ray)
{
    double x_increment, y_increment;
    double x, y;
    double delta_x, delta_y;
    int steps, i;

    delta_x = ray.distance * cos(ray.angle);
    delta_y = ray.distance * sin(ray.angle);

    steps = (int)fmax(fabs(delta_x), fabs(delta_y));
    x_increment = delta_x / steps;
    y_increment = delta_y / steps;

    x = ray.x;
    y = ray.y;
    i = 0;

    while (i <= steps)
    {
        if (x >= 0 && x < map->mlx.width && y >= 0 && y < map->mlx.height)
            mlx_put_pixel(map->mlx.img, (int)x, (int)y, ft_pixel(255, 0, 0, 255));
        else
            break;
        x += x_increment;
        y += y_increment;
        i++;
    }
}

void	cast_ray(t_map *map)
{
	t_ray	ray;

    ft_bzero(&ray, sizeof(t_ray));
	ray.angle = (map->player.ray_angle - 90) * M_PI / 180.0;
	ray.x = map->player.x;
	ray.y = map->player.y;
	get_ray_distance(map, &ray);
	draw_line(map, ray);
}
