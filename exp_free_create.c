/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_free_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:47:46 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/28 14:27:06 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_export_create(void)
{
	int		len;

	len = -1;
	while (g_envi[++len])
		;
	g_exp = ft_calloc(sizeof(t_exp *), len + 1);
	while (--len >= 0)
		g_exp[len] = ft_export_new_key(g_envi[len]);
	ft_export_sort();
	if (!(ft_oldpwd_index() + 1))
		ft_add_oldpwd();
}

void			ft_export_free(void)
{
	int		i;

	i = -1;
	while (g_exp[++i])
	{
		free(g_exp[i]->key);
		free(g_exp[i]->value);
		free(g_exp[i]);
	}
	free(g_exp);
}

void			ft_cd_error(int i)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(g_buf[i][1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd(10, 2);
	g_code = 1;
}
