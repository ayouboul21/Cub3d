/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:46:36 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/17 15:01:37 by hel-magh         ###   ########.fr       */
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
		move_backward(map);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_W))
		move_forward(map);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_A))
		move_left(map);
	if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_D))
		move_right(map);
	mlx_delete_image(map->mlx.mlx, map->mlx.img);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	render_frame(map);
}
