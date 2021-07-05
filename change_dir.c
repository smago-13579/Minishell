/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:41:36 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/28 14:33:04 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_pwd_index(void)
{
	int		pwd_index;

	pwd_index = -1;
	while (ft_strcmp(g_exp[++pwd_index]->key, "PWD"))
		if (!g_exp[pwd_index + 1])
		{
			pwd_index = -1;
			break ;
		}
	return (pwd_index);
}

int				ft_oldpwd_index(void)
{
	int		oldpwd_index;

	oldpwd_index = -1;
	while (ft_strcmp(g_exp[++oldpwd_index]->key, "OLDPWD"))
		if (!g_exp[oldpwd_index + 1])
		{
			oldpwd_index = -1;
			break ;
		}
	return (oldpwd_index);
}

static void		ft_cd_home(int j, int pwd, int oldpwd)
{
	while (ft_strcmp(g_exp[++j]->key, "HOME"))
		if (!g_exp[j + 1])
		{
			ft_putstr_fd("minishell: cd: No \"HOME\" variable\n", 2);
			g_code = 1;
			return ;
		}
	chdir(g_exp[j]->value);
	pwd = ft_pwd_index();
	oldpwd = ft_oldpwd_index();
	free(g_exp[oldpwd]->value);
	g_exp[oldpwd]->value = g_exp[pwd]->value;
	g_exp[pwd]->value = getcwd(NULL, 0);
	g_code = 0;
}

static void		ft_cd_oldpwd(void)
{
	char	*tmp;
	int		pwd_index;
	int		oldpwd_index;

	pwd_index = ft_pwd_index();
	oldpwd_index = ft_oldpwd_index();
	if (!g_exp[oldpwd_index]->value)
	{
		ft_putstr_fd("minishell: cd: No \"OLDPWD\" value\n", 2);
		g_code = 1;
		return ;
	}
	chdir(g_exp[oldpwd_index]->value);
	tmp = g_exp[oldpwd_index]->value;
	g_exp[oldpwd_index]->value = g_exp[pwd_index]->value;
	g_exp[pwd_index]->value = tmp;
	g_code = 0;
}

void			ft_cd(int i, int j)
{
	int		pwd;
	int		oldpwd;

	ft_pwd_oldpwd_check(&pwd, &oldpwd);
	if (!(g_buf[i][1]))
		ft_cd_home(j, pwd, oldpwd);
	else if (ft_strcmp(g_buf[i][1], "-") == 0)
		ft_cd_oldpwd();
	else if (!(chdir(g_buf[i][1]) + 1))
		ft_cd_error(i);
	else
	{
		free(g_exp[oldpwd]->value);
		g_exp[oldpwd]->value = g_exp[pwd]->value;
		g_exp[pwd]->value = getcwd(NULL, 0);
		g_code = 0;
	}
}
