/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/29 16:45:10 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	color(mlx_image_t *img, uint32_t color, t_map *map)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < img->height / map->rows * map->i)
	{
		j = 0;
		while (j < img->width / map->cols * map->j)
		{
			mlx_put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	color_player(mlx_image_t *img, uint32_t color)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	player_color;

	i = 0;
	player_color = ft_pixel(0, 0, 255, 0);
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			if (i >= img->height / 2 && j >= img->width / 4 && j <= img->width * 3 / 4)
				mlx_put_pixel(img, j, i, player_color);
			else
				mlx_put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 800;
	mlx->mlx = mlx_init(mlx->width, mlx->height, "cub3d", true);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
}

void ft_hook(void* param)
{
	t_mlx	*mlx = (t_mlx *)param;

	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
}

void	render_frame(t_map *map)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map[i][j] == '1')
			{
				(1) && (map->i = i, map->j = j);
				color(map->mlx.img, ft_pixel(255, 255, 255, 255), map);
			}
			else if (map->map[i][j] == '0' || map->map[i][j] == ' ')
			{
				(1) && (map->i = i, map->j = j);
				color(map->mlx.img, ft_pixel(0, 0, 0, 0), map);
			}
			j++;
		}
		i++;
	}
	mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}

void	render_map(t_map *map)
{
	init_mlx(&map->mlx);
	render_frame(map);
	mlx_loop_hook(map->mlx.mlx, ft_hook, &map->mlx);
	mlx_loop(map->mlx.mlx);
	mlx_terminate(map->mlx.mlx);
}
