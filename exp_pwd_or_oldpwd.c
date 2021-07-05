/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_pwd_or_oldpwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:47:46 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/28 14:29:01 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_add_pwd(void)
{
	char	*tmp;
	char	*tmp2;
	t_exp	*pwd;
	int		index;
	t_exp	**tmp3;

	tmp2 = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", tmp2);
	free(tmp2);
	pwd = ft_export_new_key(tmp);
	free(tmp);
	index = -1;
	while (g_exp[++index])
		;
	tmp3 = (t_exp **)ft_calloc(sizeof(t_exp *), index + 2);
	index = -1;
	while (g_exp[++index])
		tmp3[index] = g_exp[index];
	tmp3[index] = pwd;
	free(g_exp);
	g_exp = tmp3;
	ft_export_sort();
}

void			ft_add_oldpwd(void)
{
	t_exp	**tmp;
	t_exp	*oldpwd;
	int		index;

	oldpwd = ft_export_new_key("OLDPWD");
	index = -1;
	while (g_exp[++index])
		;
	tmp = (t_exp **)ft_calloc(sizeof(t_exp *), index + 2);
	index = -1;
	while (g_exp[++index])
		tmp[index] = g_exp[index];
	tmp[index] = oldpwd;
	free(g_exp);
	g_exp = tmp;
	ft_export_sort();
}

void			ft_pwd_oldpwd_check(int *pwd, int *oldpwd)
{
	if ((*pwd = ft_pwd_index()) == -1)
	{
		ft_add_pwd();
		*pwd = ft_pwd_index();
	}
	if ((*oldpwd = ft_oldpwd_index()) == -1)
	{
		ft_add_oldpwd();
		*oldpwd = ft_oldpwd_index();
	}
}
