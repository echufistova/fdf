#include <stdio.h>
#include "fdf.h"


void get_line(char *line)
{
    int i;
}

int main(int ac, char **av)
{
    int fd;
    char *line;

    fd = open(av[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        get_line(line);
        ft_strdel(&line);
    }
    printf("Hello, World!\n");
    return 0;
}