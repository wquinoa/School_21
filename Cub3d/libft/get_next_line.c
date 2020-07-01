/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 05:54:10 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 16:43:37 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	int		l;

	if (!s2)
		return (d = ft_strdup(s1));
	if (!s1)
		return (d = ft_strdup(s2));
	l = (ft_strchr(s1, '\0') - s1) + (ft_strchr(s2, '\0') - s2) + 1;
	if (!(d = (char *)malloc(l * sizeof(char))))
		return (NULL);
	ft_strlcpy(d, s1, l);
	ft_strlcat(d, s2, l);
	return (d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*d;
	size_t		size;

	size = (ft_strchr(s + start, '\0') - (s + start));
	size = (size > len) ? len : size;
	if (!(d = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(d, &s[start], size + 1);
	return (d);
}

/*
**	Here it actually writes the line. Whenever end is NULL,
**	the program has reached the end of file. Lots of malloc
**	checks later the remainder is either written to fd_tab
**	for later use (n) or written to line (0) before exiting.
**	Also, in case of \n preceding \0, it's necessary to add.
**	If res is not initialized to NULL it will SSEGV on linux.
*/

int		write_next_line(char **line, char **fd_tab)
{
	char			*res;
	char			*end;

	if (!(end = ft_strchr(*fd_tab, '\n')))
		end = ft_strchr(*fd_tab, '\0');
	res = NULL;
	if (*end == '\n')
		if (!(res = ft_strdup(end + 1)))
			return (-1);
	if (!(*line = ft_substr(*fd_tab, 0, (end - *fd_tab))))
		return (-1);
	free(*fd_tab);
	*fd_tab = res;
	return (res != NULL);
}

/*
**	Checks for BUFFER_SIZE and fd being less than 0 are not needed
**	If Buff_size is 0 it's still possible to read the file, it just
**	cant write. If fd is < 0, read will return -1 anyway.
*/

int		check_next_line(int fd, char **line, char **buf)
{
	if (!line)
		return (-1);
	if (!(*buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (read(fd, *buf, 0) < 0)
	{
		free(*buf);
		return (-1);
	}
	return (1);
}

/*
**	Start the program. Using make_next_line ckeck the inputs
**	and allocate BUFFER_SIZE of memory.
**	Strjoin will handle the cases when fd_tab is initially empty.
**	If it finds a \n or EOF, it goes to write_next_line.
*/

int		get_next_line(int fd, char **line)
{
	static char	*fd_tab[FD_LIMIT];
	int			flag;
	char		*buf;
	char		*tmp;

	if ((flag = check_next_line(fd, line, &buf)) < 0)
		return (-1);
	while ((flag = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[flag] = '\0';
		if (!(tmp = ft_strjoin(fd_tab[fd], buf)))
		{
			free(buf);
			return (-1);
		}
		fd_tab[fd] ? free(fd_tab[fd]) : 0;
		fd_tab[fd] = tmp;
		if (ft_strchr(fd_tab[fd], '\n') || !flag)
		{
			free(buf);
			return (write_next_line(line, &fd_tab[fd]));
		}
	}
	free(buf);
	return (-1);
}
