/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 21:16:06 by smago             #+#    #+#             */
/*   Updated: 2020/12/20 17:05:02 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_redirect2(char *str, char *str2)
{
	g_data.end += 2;
	while (ft_strchr(" \t", str[g_data.end]))
		g_data.end++;
	g_data.start = g_data.end;
	str2 = fill_token3(str);
	g_data.fd[1] = open(str2, O_APPEND | O_WRONLY | O_CREAT, 00644);
	return (str2);
}

char	*ft_redirect1(char *str, char *str2)
{
	if (g_data.fd[1] >= 0)
		close(g_data.fd[1]);
	if (str[g_data.end] == '>' && str[g_data.end + 1] == '>')
		str2 = ft_redirect2(str, NULL);
	else if (str[g_data.end] == '>')
	{
		g_data.end++;
		while (ft_strchr(" \t", str[g_data.end]))
			g_data.end++;
		g_data.start = g_data.end;
		str2 = fill_token3(str);
		g_data.fd[1] = open(str2, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	}
	if (g_data.fd[1] < 0)
	{
		free(str2);
		return (NULL);
	}
	return (str2);
}

void	check_fds(void)
{
	if (g_data.fd[0] >= 0)
		close(g_data.fd[0]);
	if (g_data.fd_p[0] >= 0)
	{
		close(g_data.fd_p[0]);
		g_data.fd_p[0] = -1;
		dup2(g_data.fd_tmp, 0);
		close(g_data.fd_tmp);
	}
}

int		ft_redirect(char *str)
{
	char *str2;

	if (str[g_data.end] == '>')
	{
		if (!(str2 = ft_redirect1(str, NULL)))
			return (-1);
	}
	else
	{
		check_fds();
		g_data.end++;
		while (ft_strchr(" \t", str[g_data.end]))
			g_data.end++;
		g_data.start = g_data.end;
		str2 = fill_token3(str);
		if ((g_data.fd[0] = open(str2, O_RDONLY)) < 0)
		{
			free(str2);
			return (-1);
		}
	}
	free(str2);
	return (0);
}
