/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:45:34 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/23 22:20:22 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_g_envi_free(int i)
{
	while (g_envi[++i])
		free(g_envi[i]);
	free(g_envi);
}

void		ft_g_envi_update(void)
{
	int		i;
	int		count;
	char	*tmp;

	i = -1;
	count = 0;
	ft_g_envi_free(i);
	while (g_exp[++i])
		if (g_exp[i]->value)
			count++;
	g_envi = ft_calloc(sizeof(char *), count + 1);
	i = -1;
	count = 0;
	while (g_exp[++i])
	{
		if (g_exp[i]->value)
		{
			tmp = ft_strjoin(g_exp[i]->key, "=");
			g_envi[count] = tmp;
			tmp = ft_strjoin(tmp, g_exp[i]->value);
			free(g_envi[count]);
			g_envi[count] = tmp;
			count++;
		}
	}
}
