/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 19:20:03 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 21:46:48 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_status(int status)
{
	if (WIFEXITED(status))
		g_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_code = 128 + WTERMSIG(status);
}

int		ft_exit_code2(char *str2)
{
	while (*str2 == ' ' || *str2 == '\t')
		str2++;
	if (*str2 == '+' || *str2 == '-')
		str2++;
	while (*str2 != '\0' && ft_strchr("1234567890", *str2) != NULL)
		str2++;
	while (*str2 == ' ' || *str2 == '\t')
		str2++;
	if (*str2 != '\0')
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: numeric argument required\n", 1);
		g_code = 255;
		return (1);
	}
	return (0);
}

int		ft_exit_code(int len, int i)
{
	while (g_buf[len][i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		g_code = 1;
		return (1);
	}
	if (i > 1)
	{
		if (ft_exit_code2(g_buf[len][1]) == 1)
			exit(g_code);
		g_code = atoi(g_buf[len][1]);
	}
	if (g_code > 255)
		g_code %= 256;
	exit(g_code);
	return (0);
}
