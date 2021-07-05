/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:58:21 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/27 19:40:53 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_export_delete(int i)
{
	t_exp	**tmp;
	int		index;
	int		count;

	count = -1;
	index = -1;
	while (g_exp[++index])
		;
	tmp = ft_calloc(sizeof(t_exp *), index);
	index = -1;
	while (g_exp[++index])
		if (index != i)
			tmp[++count] = g_exp[index];
	free(g_exp[i]->key);
	if (g_exp[i]->value)
		free(g_exp[i]->value);
	free(g_exp[i]);
	free(g_exp);
	g_exp = tmp;
}

void		ft_unset(int i)
{
	int		index;
	int		count;
	int		find;

	index = 0;
	while (g_buf[i][++index])
	{
		find = -1;
		count = -1;
		while (g_exp[++count])
			if (ft_strcmp(g_exp[count]->key, g_buf[i][index]) == 0)
				find = count;
		if (find != -1)
			ft_export_delete(find);
	}
	g_code = 0;
}

void		ft_export_print(void)
{
	int		i;

	i = -1;
	while (g_exp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(g_exp[i]->key, 1);
		if (g_exp[i]->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(g_exp[i]->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd(10, 1);
	}
	g_code = 0;
}

void		ft_export_sort(void)
{
	int		i;
	int		j;
	t_exp	*tmp;

	i = -1;
	while (g_exp[++i + 1])
	{
		j = -1;
		while (g_exp[++j + i + 1])
		{
			if (ft_strcmp(g_exp[j]->key, g_exp[j + 1]->key) > 0)
			{
				tmp = g_exp[j];
				g_exp[j] = g_exp[j + 1];
				g_exp[j + 1] = tmp;
			}
		}
	}
}
