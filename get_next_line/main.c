/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 11:40:09 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/18 13:05:54 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
    int fd, ret;
    char *str[1];
    fd = open("test.txt", O_RDONLY);
    while ((ret = get_next_line(fd, str)) > 0)
    {
        printf("%s\n", str[0]);
        free(str[0]);
    }
    if (ret == 0)
    {
         printf("%s", str[0]);
         free(str[0]);
    }
    if (ret == -1)
        printf("%d", ret);
    return (0);
}
