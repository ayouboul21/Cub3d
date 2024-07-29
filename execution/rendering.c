/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/29 15:46:48 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	color(mlx_image_t *img, uint32_t color)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
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

void	init_mlx(t_mlx *mlx, t_map *map)
{
	mlx->width = 800;
	mlx->height = 800;
	mlx->mlx = mlx_init(mlx->width, mlx->height, "cub3d", true);
	mlx->wall_img = mlx_new_image(mlx->mlx,
		mlx->width / map->cols, mlx->height / map->rows);
	mlx->ground_img = mlx_new_image(mlx->mlx,
		mlx->width / map->cols, mlx->height / map->rows);
	mlx->player_img = mlx_new_image(mlx->mlx,
		mlx->width / map->cols, mlx->height / map->rows);
	printf("width: %d\nHeight: %d\n", mlx->wall_img->width, mlx->wall_img->height);
	color(mlx->wall_img, ft_pixel(255, 0, 0, 0));
	color(mlx->ground_img, ft_pixel(0, 0, 0, 0));
	color_player(mlx->player_img, ft_pixel(0, 0, 0, 0));
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
	int32_t	offset_x;
	int32_t	offset_y;

	i = 0;
	offset_x = map->mlx.width / map->cols;
	offset_y = map->mlx.height / map->rows;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map[i][j] == '1')
				mlx_image_to_window(map->mlx.mlx, map->mlx.wall_img, i * offset_x, j * offset_y);
			else if (map->map[i][j] == '0' || map->map[i][j] == ' ')
				mlx_image_to_window(map->mlx.mlx, map->mlx.ground_img, i * offset_x, j * offset_y);
			else
				mlx_image_to_window(map->mlx.mlx, map->mlx.player_img, i * offset_x, j * offset_y);
			j++;
		}
		i++;
	}
}

void	render_map(t_map *map)
{
	init_mlx(&map->mlx, map);
	render_frame(map);
	mlx_loop_hook(map->mlx.mlx, ft_hook, &map->mlx);
	mlx_loop(map->mlx.mlx);
	mlx_terminate(map->mlx.mlx);
}
