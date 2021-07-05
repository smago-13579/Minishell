/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_me.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 04:38:20 by esnowbal          #+#    #+#             */
/*   Updated: 2020/12/27 19:56:14 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command_me(int i)
{
	int		j;

	j = -1;
	if (ft_strcmp(g_buf[i][0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(g_buf[i][0], "cd") == 0)
		ft_cd(i, j);
	else if (ft_strcmp(g_buf[i][0], "env") == 0)
		ft_env(j);
	else if (ft_strcmp(g_buf[i][0], "echo") == 0)
		ft_echo(i, 1);
	else if (ft_strcmp(g_buf[i][0], "export") == 0)
	{
		if (!g_buf[i][1])
			ft_export_print();
		else
			ft_export_add(i);
	}
	else if (ft_strcmp(g_buf[i][0], "unset") == 0)
	{
		if (g_buf[i][1])
			ft_unset(i);
	}
}
