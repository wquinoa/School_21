#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
int main()
{
    int fd, ret;
    char *str[10];
    fd = open("test.txt", O_RDONLY);
    while ((ret = get_next_line(fd, str)) > 0)
    {
        printf("[%d] - %s\n", ret, str[0]);
        free(str[0]);
    }
    if (ret == 0)
    {
         printf("[%d] -  %s\n", ret, str[0]);
         free(str[0]);
    }
    if (ret == -1)
        printf("%d", ret);
    return (0);
}