#include "so_long.h"

int32_t main(int argc, char **argv)
{
    t_map *map;
    int    py;
    int    px;

    if (argc != 2)
    {
        write(2, "Usage: ./so_long <map.ber>\n", 28);
        return (1);
    }

    map = load_map(argv[1]);
    if (!map)
    {
        write(2, "Error: load_map\n", 16);
        return (1);
    }

    printf("Map size: width = %d, height = %d\n", map->width, map->height);

    if (!check_chars(map))
    {
        write(2, "Error: invalid chars / borders / counts\n", 41);
        return (1);
    }
    printf("check_chars: OK\n");

    if (!find_player(map, &py, &px))
    {
        write(2, "Error: no player found\n", 23);
        return (1);
    }
    printf("Player at: y = %d, x = %d\n", py, px);

    if (!check_path(map))
    {
        write(2, "Error: no valid path\n", 21);
        return (1);
    }
    printf("check_path: OK (all C reachable and exit reachable)\n");

    // affichage brut de la map pour vérif visuelle
    int y = 0;
    while (y < map->height)
    {
        printf("%s", map->grid[y]);
        y++;
    }

    // TODO: penser à free map->grid et map ici quand tu écriras ta fonction de free
    return (0);
}
