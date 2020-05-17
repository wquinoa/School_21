/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:15:04 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/09 09:59:58 by wquinoa          ###   ########.fr       */
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
	ft_putstr_fd(("	->\033[94minput\033[0m: "), 1);
	ft_putendl_fd(str, 1);
	ft_putstr_fd(("\n	\033[94mstdatoi\033[0m: "), 1);
	ft_putnbr_fd(atoi(str), 1);		//	atoi
	ft_putstr_fd(("\n	\033[94mft_atoi\033[0m: "), 1);
	ft_putnbr_fd(ft_atoi(str), 1);  //	ft _atoi
	ft_putstr_fd(("\n\n	\033[94mft_itoa\033[0m: "), 1); //	ft _itoa
	ft_putstr_fd(dst, 1);
	ft_putendl_fd("\n", 1);
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
	{
		ft_putendl_fd("couldnt allocate memory, try again", 1);
		return ;
	}
	if (!(str2 = (char *)calloc(n, sizeof(char))))
	{
		ft_putendl_fd("couldnt allocate memory, try again", 1);
		free(str1);
		return ;
	}
	ft_putstr_fd("\033[94m  ---strl_cpy---\033[0m", 1);
	ft_putstr_fd("\n   returned: ", 1);
	ft_putnbr_fd(strlcpy(str1, dst, n), 1);		//	strlcpy
	ft_putstr_fd("\n  copied to dst: ", 1);
	ft_putendl_fd(str1, 1);
	ft_putstr_fd("\n\033[94m  --ft_strlcpy--\033[0m\n   returned: ", 1);	//	ft_strlcpy
	ft_putnbr_fd(ft_strlcpy(str2, dst, n), 1);
	ft_putstr_fd("\n  copied to dst: ", 1);
	ft_putendl_fd(str2, 1);

	ft_putstr_fd("\033[94m\n  ---strl_cat---\033[0m\n   returned: ", 1);	//	strlcat
	ft_putnbr_fd(strlcat(str1, src, n), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("  added to dst: ", 1);
	ft_putendl_fd(str1, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("\033[94m  --ft_strlcat--\033[0m\n   returned: ", 1); //	ft_strlcat
	ft_putnbr_fd(ft_strlcat(str2, src, n), 1);
	ft_putstr_fd("\n  added to dst: ", 1);
	ft_putendl_fd(str2, 1);
	ft_putstr_fd("\n   \033[94mft_strjoin\033[0m: ", 1);
	ft_putendl_fd(ft_strjoin(dst, src), 1);

	free(str1);
	free(str2);
}

char	*ft_bool(int i)
{
	return ((i >= 1) ? "True" : "False");
}

void	t_alpha(int c)
{
	char *tab[7];
	int (*func[8])(int);
	func[0] = &ft_isalpha;		tab[0] = "	      \033[94mft_isalpha\033[0m: ";
	func[1] = &ft_isdigit;		tab[1] = "\n	      \033[94mft_isdigit\033[0m: ";
	func[2] = &ft_isalnum;		tab[2] = "\n	      \033[94mft_isalnum\033[0m: ";
	func[3] = &ft_isascii;		tab[3] = "\n	      \033[94mft_isascii\033[0m: ";
	func[4] = &ft_isprint;		tab[4] = "\n	      \033[94mft_isprint\033[0m: ";
	func[5] = &ft_toupper;		tab[5] = "\n	      \033[94mft_toupper\033[0m: ";
	func[6] = &ft_tolower;		tab[6] = "\n	      \033[94mft_tolower\033[0m: ";
	func[7] = NULL;

	for (int i = 0; func[i]; i++)
	{
		ft_putstr_fd(tab[i], 1);
		if (i > 4)
			ft_putchar_fd(func[i](c), 1);
		else
			ft_putstr_fd(ft_bool(func[i](c)), 1);
	}
	ft_putendl_fd("\n", 1);
}

void	t_strchr(char *s, char c)
{
	char *dst;
	char *tab[4];
	char *(*func[5])(const char *s, int c);
	func[0] = &strchr;		tab[0] = "      \033[94mstrchr\033[0m: [";
	func[1] = &ft_strchr;	tab[1] = "     \033[94mft_strchr\033[0m: [";
	func[2] = &strrchr;		tab[2] = "      \033[94mstrrchr\033[0m: [";
	func[3] = &ft_strrchr;	tab[3] = "     \033[94mft_strrchr\033[0m: [";
	func[4] = NULL;

	for (int i = 0; func[i]; i++)
	{
		i += (s == NULL);
		ft_putstr_fd(tab[i], 1);
		if(!(dst = func[i](s, c)))
		{
			ft_putendl_fd("NULL]\n\n", 1);
			continue ;
		}
		else
		{
			ft_putstr_fd(dst, 1);
			ft_putendl_fd("]\n",1);
		}
	}
}

void	t_strdup(const char *str)
{
	char *dst;
	char *tab[2];
	char *(*func[3])(const char *s);

	func[0] = &strdup;		tab[0] = "	     \033[94mstrdup\033[0m:  [";
	func[1] = &ft_strdup;	tab[1] = "	   \033[94mft_strdup\033[0m: [";
	func[2] = NULL;
	for (int i = 0; func[i]; i++)
	{
		i += (str == NULL);
		ft_putstr_fd(tab[i], 1);
		if(!(dst = func[i](str)))
		{
			ft_putendl_fd("NULL]\n\n", 1);
			return ;
		}
		else if (dst[0] == '\0')
		{
			ft_putendl_fd("\\0]\n\n", 1);
			return ;
		}
		else
		{
			ft_putstr_fd(dst, 1);
			ft_putendl_fd("]\n",1);
		}
		if (dst)
			free(dst);
	}
	ft_putendl_fd("",1);
}

void	t_substr(char const *s, unsigned int start, size_t len)
{
	char *dst;

	ft_putstr_fd("   \033[94mYour substr returned\033[0m: [", 1);
	if(!(dst = ft_substr(s, start, len)))
	{
		ft_putendl_fd("NULL] SHOULD RETURN \"\0\"\n\n", 1);
		return ;
	}
	else if (dst[0] == '\0')
	{
		ft_putendl_fd("\\0] nice!\n\n", 1);
		return ;
	}
	else
	{
		ft_putstr_fd(dst, 1);
		ft_putendl_fd("]\n\n",1);
		if (dst)
			free(dst);
	}
}

void		t_split(char *str, char *c)
{
	char	**tab;
	char	*dst;

	dst = ft_strtrim(str, c);
	tab = ft_split(str, c[0]);

	ft_putstr_fd("\033[94mYour strtrim:\033[0m [", 1);
	if (!dst)
		ft_putstr_fd("NULL", 1);
	else
		ft_putstr_fd(dst, 1);
	ft_putendl_fd("]", 1);
	if (dst)
		free (dst);
	dst = ft_join(tab, "][");
	ft_putstr_fd("\033[94mYour  split : \033[0m[", 1);
	if (tab && *tab)
		ft_tabclear(tab, ft_tablen(tab));
	if (!dst)
	{
		ft_putendl_fd("NULL]\n\n", 1);
		return ;
	}
	else
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
	int flag = 0;

	if (argc == 2)
	{
		if (strcmp(argv[1], "help") == 0)
		{
			ft_putendl_fd("+-----------------=====-----------------+\n", 1);
			ft_putendl_fd("    \e[1mformat: ./a.out [name] [args ...]\e[0m\n", 1);
			ft_putendl_fd("      in: ./a.out strlcat dst src 7", 1);
			ft_putendl_fd("       out: ft_strlcat(dst, src, 7)\n", 1);
			ft_putendl_fd("    This test will ONLY work if your\n     ft_put* functions are correct.\n", 1);
			ft_putendl_fd("    Compile with your libft.a first.\n\n", 1);
			ft_putendl_fd("    tests ft_strl* ft_split, ft_join     \n", 1);
			ft_putendl_fd("    ft_strtrim ft_atoi ft_itoa           \n", 1);
			ft_putendl_fd("+-----------------=====-----------------+", 1);
			flag = 2;
		}
	}
	if (argc >= 2)
	{
		if ((strcmp(argv[1], "split") == 0) || (strcmp(argv[1], "strtrim") == 0))
		{
			ft_putendl_fd("+---------------------------------------+", 1);
			ft_putendl_fd("|         \e[1mft_strtrim && ft_split\e[0m        |", 1);
			ft_putendl_fd("+---------------------------------------+\n\n", 1);
			if (argc == 4)
				t_split(argv[2], argv[3]);
			else
			{
				ft_putendl_fd("ft_strtrim(NULL, \'a\')", 1);
				ft_putendl_fd("ft_split(NULL, \'a\')", 1);
				t_split(NULL, "a");
			}
		}
		if (strcmp(argv[1], "strdup") == 0)
		{
			ft_putendl_fd("+---------------------------------------+", 1);
			ft_putendl_fd("|               \e[1mft_strdup   \e[0m            |", 1);
			ft_putendl_fd("+---------------------------------------+\n\n", 1);
			if (argc >= 3)
				t_strdup(argv[2]);
			else
			{
				ft_putendl_fd("ft_strdup(NULL) -- std strdup will SEGV", 1);
				t_strdup(NULL);
			}
		}
		if (((strcmp(argv[1], "atoi")) == 0 || (strcmp(argv[1], "itoa")) == 0) && argc == 3)
		{
			ft_putendl_fd("+-----------------=====-----------------+", 1);
			ft_putendl_fd("|     \e[1mft_atoi vs std_atoi + ft_itoa\e[0m     |", 1);
			ft_putendl_fd("+-----------------=====-----------------+\n", 1);
			str1 = argv[2];
			n = atoi(str1);
			t_atoi(str1, n);
		}
		if (strncmp(argv[1], "sub", 3) == 0)
		{
			ft_putendl_fd("+---------------------------------------+", 1);
			ft_putendl_fd("|               \e[1mft_substr\e[0m               |", 1);
			ft_putendl_fd("+---------------------------------------+\n\n", 1);
			if (argc <= 4)
			{
				ft_putendl_fd("ft_substr(NULL, 0, 5):", 1);
				t_substr(NULL, 0, 5);
				ft_putendl_fd("ft_substr(NULL, 2, 5):", 1);
				t_substr(NULL, 2, 5);
			}
			else if (ft_isdigit(argv[3][0]) && ft_isdigit(argv[4][0]))
				t_substr(argv[2], atoi(argv[3]), atoi(argv[4]));
		}
		flag = 1;
	}
	if (argc >= 3)
	{
		if (strncmp(argv[1], "is", 2) == 0)
		{
			ft_putendl_fd("+-----------------=====-----------------+", 1);
			ft_putendl_fd("|            \e[1mft_is* package\e[0m             |", 1);
			ft_putendl_fd("+-----------------=====-----------------+\n", 1);
			if (argc == 3)
				t_alpha(argv[2][0]);
			else
				t_alpha(atoi(argv[2]));
		}
		if (strcmp (argv[1], "strchr") == 0)
		{
			ft_putendl_fd("+-----------------=====-----------------+", 1);
			ft_putendl_fd("|             \e[1mft_str(r)chr\e[0m              |", 1);
			ft_putendl_fd("+-----------------=====-----------------+\n", 1);
			if (argc < 4)
			{
				ft_putendl_fd("ft_strchr(NULL, 'c') -- std strchr will SEGV", 1);
				t_strchr(NULL, 'c');
			}
			else
				t_strchr(argv[2], argv[3][0]);
		}
		flag = 1;
	}
	if (argc >= 4)
	{
		if ((strncmp(argv[1], "strl", 4) == 0 || strcmp(argv[1], "strjoin") == 0))
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
			}
			flag = 1;
		}
	}
	if (flag == 1)
	{
		ft_putendl_fd("+-----------------=====-----------------+", 1);
		ft_putendl_fd("|Powered by YOUR ft_put*_fd functions 🔥|", 1);
		ft_putendl_fd("+-----------------=====-----------------+", 1);
	}
	if (flag == 0)
	{
		ft_putendl_fd("+-----------------=====-----------------+\n", 1);
		ft_putendl_fd("   This test uses a lot of functions    ", 1);
		ft_putendl_fd("       from your libft to work.         ", 1);
		ft_putendl_fd("        Now type ./a.out help.           \n",1);
		ft_putendl_fd("+-----------------=====-----------------+", 1);
		return (0);
	}
}