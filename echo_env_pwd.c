/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:36:52 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/26 21:56:12 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo2(int i, int j)
{
	while (g_buf[i][j])
	{
		ft_putstr_fd(g_buf[i][j++], 1);
		if (g_buf[i][j])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd(10, 1);
}

int			ft_n_echo(char *str)
{
	int k;

	k = 2;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[k] && str[k] == 'n')
			k++;
		if (str[k] == '\0')
			return (1);
	}
	return (0);
}

void		ft_echo(int i, int j)
{
	if (g_buf[i][j])
	{
		if (ft_n_echo(g_buf[i][j]))
		{
			while (g_buf[i][j] && ft_n_echo(g_buf[i][j]))
				j++;
			while (g_buf[i][j])
			{
				ft_putstr_fd(g_buf[i][j++], 1);
				if (g_buf[i][j])
					ft_putchar_fd(' ', 1);
			}
		}
		else
			ft_echo2(i, j);
	}
	else
		ft_putchar_fd(10, 1);
	g_code = 0;
}

void		ft_env(int j)
{
	while (g_exp[++j])
	{
		if (g_exp[j]->value)
		{
			ft_putstr_fd(g_exp[j]->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(g_exp[j]->value, 1);
			ft_putchar_fd(10, 1);
		}
	}
	g_code = 0;
}

void		ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_putstr_fd(tmp, 1);
	ft_putchar_fd(10, 1);
	free(tmp);
	g_code = 0;
}
