/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:15:04 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/07 22:57:06 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

size_t		ft_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL && tab)
		i++;
	return (i);
}

void		ft_tabclear(char **tab, int len)
{
	int		i;

	if (!tab)
		return ;
	i = -1;
	while (++i < len)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	}
	free(tab);
	tab = NULL;
}

char		**ft_tabmap(char **tab, char *(*f)(const char *))
{
	char	**res;
	int		len;
	int		l;
	int		i;

	if (!tab || !f)
		return (NULL);
	len = ft_tablen(tab);
	if (!(res = (char **)malloc((sizeof(char *) * (len + 1)))))
		return (NULL);
	i = -1;
	while (++i < len)
	{
		l = ft_strlen(tab[i]);
		res[i] = (char *)ft_calloc(l + 1, sizeof(char));
		if (!(res[i]))
		{
			ft_tabclear(res, i + 1);
			return (NULL);
		}
		res[i] = ft_strdup(tab[i]);
	}
	res[i] = NULL;
	return (res);
}

char		*ft_strjoin_dlm(char *s1, char *s2, char *s3)
{
	char	*res;
	char	*tmp;

	if (!s1 || !s2 || !s3)
		return (NULL);
	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	if (!(res = ft_strjoin(tmp, s3)))
		return (NULL);
	free(tmp);
	return (res);
}

void		t_atoi(char *str, int n)
{
	char	*dst;

	dst = ft_itoa(n);
	ft_putstr_fd(("  input: "), 1);
	ft_putendl_fd(str, 1);
	ft_putstr_fd(("stdatoi: "), 1);
	ft_putnbr_fd(atoi(str), 1);		//	atoi
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(("ft_atoi: "), 1);
	ft_putnbr_fd(ft_atoi(str), 1);  //	ft _atoi
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(("ft_itoa: "), 1); //	ft _itoa
	ft_putstr_fd(dst, 1);
	ft_putchar_fd('\n', 1);
	free(dst);
}

char		*ft_join(char **tab, char *dlm)
{
	char	*tmp;
	char	*res;
	int		i;

	if (!tab || !*tab || !dlm)
		return (NULL);
	if (!(res = ft_strdup(*tab)))
		return (NULL);
	i = 0;
	while (++i && tab[i])
	{
		if (!(tmp = ft_strjoin_dlm(res, dlm, tab[i])))
		{
			free(res);
			return (NULL);
		}
		if (!(res = ft_strdup(tmp)))
		{
			free(tmp);
			return (NULL);
		}
	}
	free(tmp);
	return (res);
}

void		t_strl(char *dst, char* src, size_t n)
{
	char	*str1;
	char	*str2;

	if (!(str1 = (char *)calloc(n, sizeof(char))))
		return ;
	if (!(str2 = (char *)calloc(n, sizeof(char))))
	{
		free(str1);
		return ;
	}

	ft_putstr_fd("---strl_cpy---      ft_strjoin: ", 1);
	ft_putendl_fd(ft_strjoin(dst, src), 1);
	ft_putstr_fd("returned: ", 1);
	ft_putnbr_fd(strlcpy(str1, dst, n), 1);		//	strlcpy
	ft_putendl_fd("", 1);
	ft_putstr_fd("copied to dst: ", 1);
	ft_putendl_fd(str1, 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("--ft_strlcpy--\nreturned: ", 1);	//	ft_strlcpy
	ft_putnbr_fd(ft_strlcpy(str2, dst, n), 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("copied to dst: ", 1);
	ft_putendl_fd(str2, 1);
	ft_putendl_fd("", 1);

	ft_putstr_fd("---strl_cat---\nreturned: ", 1);	//	strlcat
	ft_putnbr_fd(strlcat(str1, src, n), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("added to dst: ", 1);
	ft_putendl_fd(str1, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("--ft_strlcat--\nreturned: ", 1); //	ft_strlcat
	ft_putnbr_fd(ft_strlcat(str2, src, n), 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("added to dst: ", 1);
	ft_putendl_fd(str2, 1);
	if(str1)
		free(str1);
	if(str2)
		free(str2);
}

void		t_split(char *str, char *c)
{
	char	**tab;
	char	*dst;

	tab = ft_split(str, c[0]);

	ft_putstr_fd("\033[94mYour strtrim:\033[0m [", 1);
	ft_putstr_fd((dst = ft_strtrim(str, c)), 1);
	ft_putendl_fd("]", 1);
	if (dst)
		free (dst);
	dst = ft_join(tab, "][");
	ft_putstr_fd("\033[94mYour  split : \033[0m[", 1);
	if (tab && *tab)
		ft_tabclear(tab, ft_tablen(tab));
	ft_putstr_fd(dst, 1);
	ft_putendl_fd("]\n\n", 1);
	if(dst)
		free(dst);
}

int			main(int argc, char **argv)
{
	char *str1;
	char *str2;
	int n;
	int flag;

	if (argc == 1 && argv)
	{
		ft_putendl_fd("type ./a.out help", 1);
		return (0);
	}
	if ((strcmp(argv[1], "atoi") == 0 || (strcmp(argv[1], "itoa") == 0)) && argc == 3)
	{
		ft_putendl_fd("+-----------------=====-----------------+", 1);
		ft_putendl_fd("|     \e[1mft_atoi vs std_atoi + ft_itoa\e[0m     |", 1);
		ft_putendl_fd("+-----------------=====-----------------+\n", 1);
		str1 = argv[2];
		n = atoi(str1);
		t_atoi(str1, n);
		flag = 1;
	}
	if ((strcmp(argv[1], "strlcat") == 0 || strcmp(argv[1], "strlcpy") == 0 || strcmp(argv[1], "strjoin") == 0) && argc >= 4)
	{
		ft_putendl_fd("+-----------------=====-----------------+", 1);
		ft_putendl_fd("| \e[1mft_strlcpy   ft_strlcat   ft_strjoin\e[0m  |", 1);
		ft_putendl_fd("+-----------------=====-----------------+\n", 1);
		if (argc == 4)
			t_strl(argv[2], argv[3], 0);
		else
		{
			n = atoi(argv[4]);
			t_strl(argv[2], argv[3], n);
			flag = 1;
		}
	}
	if (((strcmp(argv[1], "split") == 0) || (strcmp(argv[1], "strtrim") == 0)) && argc >= 2)
	{
		ft_putendl_fd("+---------------------------------------+", 1);
		ft_putendl_fd("|         \e[1mft_strtrim && ft_split\e[0m        |", 1);
		ft_putendl_fd("+---------------------------------------+\n\n", 1);
		if (argc == 4)
			t_split(argv[2], argv[3]);
		else
			t_split(NULL, "a");
		flag = 1;
	}
	if (strcmp(argv[1], "help") == 0)
	{
		ft_putendl_fd("+-----------------=====-----------------+\n", 1);
		ft_putendl_fd("    \e[1mformat: ./a.out [name] [args ...]\e[0m\n", 1);
		ft_putendl_fd("      in: ./a.out strlcat dst src 7", 1);
		ft_putendl_fd("       out: ft_strlcat(dst, src, 7)\n", 1);
		ft_putendl_fd("    This test will ONLY work if your\n     ft_put* functions are correct.", 1);
		ft_putendl_fd("    Compile with your libft.a first.\n\n", 1);
		ft_putendl_fd("    tests ft_strl* ft_split, ft_join     \n", 1);
		ft_putendl_fd("    ft_strtrim ft_atoi ft_itoa           \n", 1);
		ft_putendl_fd("+-----------------=====-----------------+", 1);
		flag = 2;
	}

	if (flag == 1)
	{
		ft_putendl_fd("+-----------------=====-----------------+", 1);
		ft_putendl_fd("|Powered by YOUR ft_put*_fd functions 🔥|", 1);
		ft_putendl_fd("+-----------------=====-----------------+", 1);
	}
	if (flag == 0)
	{
		ft_putendl_fd("a./out help", 1);
		return (0);
	}
}