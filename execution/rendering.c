/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/29 18:06:23 by hel-magh         ###   ########.fr       */
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
	uint32_t	offset_x;
	uint32_t	offset_y;

	offset_x = (img->width / map->cols) * map->j;
	offset_y = (img->height / map->rows) * map->i;
	i = offset_x;
	while (i < offset_x + img->width / map->cols)
	{
		j = offset_y;
		while (j < offset_y + img->height / map->rows)
		{
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	color_player(mlx_image_t *img, uint32_t color, t_map *map)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset_x;
	uint32_t	offset_y;

	(void)color;
	offset_x = (img->width / map->cols) * map->j;
	offset_y = (img->height / map->rows) * map->i;
	i = offset_x;
	while (i < offset_x + img->width / map->cols)
	{
		j = offset_y;
		while (j < offset_y + img->height / map->rows)
		{
			mlx_put_pixel(img, i, j, ft_pixel(0, 0, 255, 255));
			j++;
		}
		i++;
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 600;
	mlx->mlx = mlx_init(mlx->width, mlx->height, "cub3d", false);
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
				color(map->mlx.img, ft_pixel(0, 0, 0, 127), map);
			}
			else if (map->map[i][j] == '0' || map->map[i][j] == ' ')
			{
				(1) && (map->i = i, map->j = j);
				color(map->mlx.img, ft_pixel(255, 255, 255, 127), map);
			}
			else
			{
				(1) && (map->i = i, map->j = j);
				color(map->mlx.img, ft_pixel(255, 0, 0, 255), map);
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
