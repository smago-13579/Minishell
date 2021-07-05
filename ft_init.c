/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:43:07 by smago             #+#    #+#             */
/*   Updated: 2020/12/27 16:49:28 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init2(void)
{
	g_data.fd_p[0] = -1;
	g_data.fd_p[1] = -1;
	g_data.fd_p2[0] = -1;
	g_data.fd_p2[1] = -1;
	g_data.fd[0] = -1;
	g_data.fd[1] = -1;
	g_data.fd_error = 1;
	g_code = 0;
}

void	ft_init(int ac, char **av, char **envp)
{
	int i;
	int count;

	i = 0;
	count = 0;
	g_data.high = 1;
	g_data.mid = 0;
	g_data.start = 0;
	g_data.end = 0;
	g_buf = NULL;
	ft_init2();
	(void)ac;
	(void)av;
	while (envp[count])
		count++;
	g_envi = (char **)ft_calloc(sizeof(char*), (count + 1));
	while (envp[i])
	{
		g_envi[i] = ft_strdup(envp[i]);
		i++;
	}
}

int		ft_null_str(char *str)
{
	if (!str)
	{
		ft_putstr_fd("error: failed to alloc buffer: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

char	*ft_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}
