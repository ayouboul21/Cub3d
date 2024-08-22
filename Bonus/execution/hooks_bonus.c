/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:46:36 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/21 22:58:27 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	rotate_left(t_map *map)
{
	map->player.angle -= 2;
	if (map->player.angle < 0)
		map->player.angle += 360;
}

void	rotate_right(t_map *map)
{
	map->player.angle += 2;
	if (map->player.angle >= 360)
		map->player.angle -= 360;
}

void	ft_hook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(map->mlx.mlx));
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_LEFT))
		rotate_left(map);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_RIGHT))
		rotate_right(map);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_S))
		(move_backward(map), map->fm--);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_W))
		(move_forward(map), map->fm++);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_A))
		move_left(map);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_D))
		move_right(map);
	ft_mouse_hook(map);
	mlx_delete_image(map->mlx.mlx, map->mlx.img);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	render_frame(map);
}

void	mouse_vis(t_map *map)
{
	if (mlx_is_mouse_down(map->mlx.mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		mlx_set_cursor_mode(map->mlx.mlx, MLX_MOUSE_HIDDEN);
		map->m = 0;
	}
	else if (mlx_is_mouse_down(map->mlx.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_set_cursor_mode(map->mlx.mlx, MLX_MOUSE_NORMAL);
		map->m = 1;
	}
}

void	ft_mouse_hook(t_map *map)
{
	int32_t	x;
	int32_t	y;

	if (!map->m)
	{
		x = 0;
		y = 0;
		mlx_set_cursor_mode(map->mlx.mlx, MLX_MOUSE_HIDDEN);
		mlx_get_mouse_pos(map->mlx.mlx, &x, &y);
		map->player.angle -= ((map->mlx.width / 2 - x) * 180
				/ map->mlx.width) * M_PI / 4;
		if (y < 0)
			y = 0;
		else if (y >= map->mlx.height)
			y = map->mlx.height - 1;
		mlx_set_mouse_pos(map->mlx.mlx, map->mlx.width / 2, y);
	}
	mouse_vis(map);
}
