#include "cub3d.h"

void	printer(t_map *map)
{
	int	i;

	i = 0;
	printf("NO :%s\n", map->north);
	printf("SO :%s\n", map->south);
	printf("WE :%s\n", map->west);
	printf("EA :%s\n", map->east);
	printf("FLOOR :%s\n", map->floor_color);
	printf("CEILING :%s", map->ceiling_color);
	printf("MAP :\n");
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	// printf("player x : %f player y : %f\n", map->player.x, map->player.y);
}
