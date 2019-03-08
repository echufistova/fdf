#include <stdio.h>
#include "fdf.h"


void get_line(t_map *map, char *line)
{
    t_point k;
    int counter;
    char *dopline;
    char **split;

    split = ft_strsplit(line, ' ');
    while (split[k.x] != '\0')
    {
        while (split[k.y] != '\0')
    }

}

void init(t_map *map)
{
    map->list_coord = (t_list_coord*)malloc(sizeof(t_list_coord));
    map->list_coord->next = NULL;
}

int main(int ac, char **av)
{
    int fd;
    int len;
    char *line;
    t_map map;

    fd = open(av[1], O_RDONLY);
    init(&map);
    while (get_next_line(fd, &line) > 0)
    {
        get_line(&map, line);
        ft_strdel(&line);
    }
    printf("Hello, World!\n");
    return 0;
}
