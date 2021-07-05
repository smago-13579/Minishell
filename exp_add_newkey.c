/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_add_newkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:26:56 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/27 19:38:07 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_export_add(int i)
{
	int		index;
	int		count;
	t_exp	**tmp;

	count = 0;
	while (g_buf[i][++count])
	{
		index = -1;
		while (g_exp[++index])
			;
		if ((tmp = ft_export_add2(i, count, index)))
		{
			free(g_exp);
			g_exp = tmp;
			ft_export_sort();
			g_code = 0;
		}
	}
}

t_exp			**ft_export_add2(int i, int count, int index)
{
	t_exp	**tmp;
	t_exp	*new;
	int		id;

	tmp = (t_exp **)ft_calloc(sizeof(t_exp *), index + 2);
	index = -1;
	while (g_exp[++index])
		tmp[index] = g_exp[index];
	if (!(new = ft_export_new_key(g_buf[i][count])))
	{
		g_code = 1;
		free(tmp);
		return (NULL);
	}
	id = ft_export_keys_cmp(new);
	if (id < 0)
		tmp[index] = new;
	else
	{
		free(tmp[id]->value);
		tmp[id]->value = new->value;
		free(new->key);
		free(new);
	}
	return (tmp);
}

int				ft_export_keys_cmp(t_exp *elem)
{
	int		i;

	i = -1;
	while (g_exp[++i])
		if (ft_strcmp(g_exp[i]->key, elem->key) == 0)
			return (i);
	return (-1);
}

static t_exp	*ft_newkey(char *str)
{
	t_exp	*new;
	int		i;

	new = malloc(sizeof(t_exp));
	i = -1;
	while (str[++i] != '=')
		if (!str[i])
		{
			i = -1;
			break ;
		}
	if (i != -1)
	{
		new->key = ft_substr(str, 0, i);
		new->value = ft_strdup(&str[i + 1]);
	}
	else
	{
		new->key = ft_strdup(str);
		new->value = NULL;
	}
	return (new);
}

t_exp			*ft_export_new_key(char *str)
{
	t_exp	*new;

	if (ft_isalpha(*str) || *str == '_')
		new = ft_newkey(str);
	else
	{
		ft_putstr_fd("bash: export: \"", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\": invalid value\n", 1);
		return (NULL);
	}
	return (new);
}
