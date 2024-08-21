/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hands_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:36:19 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/21 18:02:25 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	hands_init(t_map *map)
{
	int	i;

	i = 0;
	map->txt2[0] = mlx_load_png("./texture/hands/011.png");
	map->txt2[1] = mlx_load_png("./texture/hands/022.png");
	map->txt2[2] = mlx_load_png("./texture/hands/033.png");
	map->txt2[3] = mlx_load_png("./texture/hands/044.png");
	map->txt2[4] = mlx_load_png("./texture/hands/055.png");
	map->txt2[5] = mlx_load_png("./texture/hands/066.png");
	map->txt2[6] = mlx_load_png("./texture/hands/077.png");
	map->txt2[7] = mlx_load_png("./texture/hands/088.png");
	while (i < 8)
	{
		if (!map->txt2[i])
			ft_exit(*map, 0);
		i++;
	}
}

void	draw_hands(t_map *map)
{
	double	h_x;
	double	h_y;
	double	j;
	double	i;
	int		index;

	h_x = map->mlx.width / 4;
	h_y = map->mlx.height / 2;
	i = h_x;
	j = h_y;
	if (map->fm > 7)
		map->fm = 0;
	if (map->fm < 0)
		map->fm = 7;
	while (i < map->mlx.width - h_x)
	{
		j = h_y;
		while (j < map->mlx.height)
		{
			map->x = (i - h_x) * map->txt2[map->fm]->width / (map->mlx.width / 2);
			map->y = (j - h_y) * map->txt2[map->fm]->height / (map->mlx.height / 2);
			index = (map->y * map->txt2[map->fm]->width + map->x) * map->txt2[map->fm]->bytes_per_pixel;
			map->clr = mlx_get_pixel(map->txt2[map->fm], map->x, map->y);
			if(map->txt2[map->fm]->pixels[index] != 0 && map->txt2[map->fm]->pixels[index + 1] != 0 
				&& map->txt2[map->fm]->pixels[index + 2] != 0)
				mlx_put_pixel(map->mlx.img, i, j, map->clr);
			j++;
		}
		i++;
	}
}
