/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/30 10:47:04 by aoulahra         ###   ########.fr       */
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

void calculate_rotated_vertices(int x, int y, float half_width, float half_height, float angle, int *vertices)
{
    float angle_rad = angle * M_PI / 180.0;
    float cos_angle = cos(angle_rad);
    float sin_angle = sin(angle_rad);

    int top_x = x;
    int top_y = y - half_height;
    int left_x = x - half_width;
    int left_y = y + half_height;
    int right_x = x + half_width;
    int right_y = y + half_height;

    vertices[0] = x + (int)((top_x - x) * cos_angle - (top_y - y) * sin_angle);
    vertices[1] = y + (int)((top_x - x) * sin_angle + (top_y - y) * cos_angle);
    vertices[2] = x + (int)((left_x - x) * cos_angle - (left_y - y) * sin_angle);
    vertices[3] = y + (int)((left_x - x) * sin_angle + (left_y - y) * cos_angle);
    vertices[4] = x + (int)((right_x - x) * cos_angle - (right_y - y) * sin_angle);
    vertices[5] = y + (int)((right_x - x) * sin_angle + (right_y - y) * cos_angle);
}

int is_inside_triangle(int i, int j, int *vertices)
{
    float alpha, beta, gamma;
    int x1 = vertices[0], y1 = vertices[1];
    int x2 = vertices[2], y2 = vertices[3];
    int x3 = vertices[4], y3 = vertices[5];

    float denominator = (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
    alpha = ((float)((y2 - y3) * (i - x3) + (x3 - x2) * (j - y3))) / denominator;
    beta = ((float)((y3 - y1) * (i - x3) + (x1 - x3) * (j - y3))) / denominator;
    gamma = 1.0f - alpha - beta;

    return (alpha >= 0 && beta >= 0 && gamma >= 0);
}


void draw_triangle(mlx_image_t *img, int offset_x, int offset_y, int map_cols, int map_rows, int x, int y, float angle)
{
    int		i = offset_x, j;
    int		img_width = img->width, img_height = img->height;
    int		cell_width = img_width / map_cols, cell_height = img_height / map_rows;
    float	half_width = cell_width / 2.0, half_height = cell_height / 2.0;
    int		vertices[6];

    calculate_rotated_vertices(x, y, half_width, half_height, angle, vertices);
    while (i < offset_x + cell_width)
    {
        j = offset_y;
        while (j < offset_y + cell_height)
        {
            if (is_inside_triangle(i, j, vertices))
                mlx_put_pixel(img, i, j, ft_pixel(0, 0, 255, 127));
            else
                mlx_put_pixel(img, i, j, ft_pixel(255, 255, 255, 127));
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
				draw_triangle(map->mlx.img, map->mlx.width / map->cols * j,
					map->mlx.height / map->rows * i, map->cols, map->rows,
					map->mlx.width / map->cols * j + map->mlx.width / map->cols / 2,
					map->mlx.height / map->rows * i + map->mlx.height / map->rows / 2, map->player.angle);
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
