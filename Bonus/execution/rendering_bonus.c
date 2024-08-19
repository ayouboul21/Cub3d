/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/19 15:39:20 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	color(mlx_image_t *img, uint32_t color, t_map *map)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset_x;
	uint32_t	offset_y;

	offset_x = (img->width / map->cols) * map->j;
	offset_y = (img->height / map->rows) * map->i;
	i = offset_x;
	while (i < offset_x + img->width / map->cols - 1)
	{
		j = offset_y;
		while (j < offset_y + img->height / map->rows - 1)
		{
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	init_map(t_map *map)
{
	map->mlx.width = 1280;
	map->mlx.height = 720;
	map->mlx.mlx = mlx_init(map->mlx.width, map->mlx.height, "cub3d", false);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	map->txt[0] = mlx_load_png(map->west);
	map->txt[1] = mlx_load_png(map->north);
	map->txt[2] = mlx_load_png(map->south);
	map->txt[3] = mlx_load_png(map->east);
	map->txt[4] = mlx_load_png("./texture/dooro.png");
	if (!map->txt[0] || !map->txt[1] || !map->txt[2]
		|| !map->txt[3] || !map->txt[4])
		ft_exit(*map, 1);
	map->cell_height = 64;
	map->cell_width = 64;
	map->player.x = map->player.x * map->cell_width + map->cell_width / 2;
	map->player.y = map->player.y * map->cell_height + map->cell_height / 2;
	map->player.speed = map->cell_width / 20;
	map->fov = 60;
	map->ray_count = map->mlx.width;
	map->player.wall_height = 64;
}

void	render_frame(t_map *map)
{
	cast_rays(map);
}

void	render_map(t_map *map)
{
	init_map(map);
	render_frame(map);
	mlx_loop_hook(map->mlx.mlx, ft_hook, map);
	mlx_loop(map->mlx.mlx);
	mlx_terminate(map->mlx.mlx);
}
