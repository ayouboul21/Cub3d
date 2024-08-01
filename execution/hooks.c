/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:46:36 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/01 10:51:19 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_map *map)
{
	mlx_delete_image(map->mlx.mlx, map->mlx.img);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	map->player.angle -= 5;
	if (map->player.angle < 0)
		map->player.angle += 360;
	render_frame(map);
}

void	rotate_right(t_map *map)
{
	mlx_delete_image(map->mlx.mlx, map->mlx.img);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	map->player.angle += 5;
	if (map->player.angle >= 360)
		map->player.angle -= 360;
	render_frame(map);
}

void	ft_hook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(map->mlx.mlx));
	else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_LEFT))
		rotate_left(map);
	else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_RIGHT))
		rotate_right(map);
	else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_S))
		move_backward(map);
	else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_W))
		move_forward(map);
	else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_A))
		move_left(map);
	else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_D))
		move_right(map);
}
