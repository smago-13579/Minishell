/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:32:28 by smago             #+#    #+#             */
/*   Updated: 2020/12/27 16:47:26 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_error(void)
{
	if (g_data.fd_error > 0)
	{
		g_data.fd_error = -1;
		print_error();
		g_code = 1;
	}
	close_fd();
}

void	print_error(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	close_pipe(void)
{
	if (g_data.fd_p[0] >= 0)
	{
		close(g_data.fd_p[0]);
		g_data.fd_p[0] = -1;
		dup2(g_data.fd_tmp, 0);
		close(g_data.fd_tmp);
	}
	else if (g_data.fd_p2[0] >= 0)
	{
		close(g_data.fd_p2[0]);
		g_data.fd_p2[0] = -1;
		dup2(g_data.fd_tmp, 0);
		close(g_data.fd_tmp);
	}
	if (g_data.fd_p[1] >= 0)
	{
		close(g_data.fd_p[1]);
		g_data.fd_p[1] = -1;
	}
	if (g_data.fd_p2[1] >= 0)
	{
		close(g_data.fd_p2[1]);
		g_data.fd_p2[1] = -1;
	}
}

void	close_fd(void)
{
	if (g_data.fd[0] >= 0)
		close(g_data.fd[0]);
	if (g_data.fd[1] >= 0)
		close(g_data.fd[1]);
	g_data.fd[0] = -1;
	g_data.fd[1] = -1;
}

void	ft_error(int i)
{
	g_data.mid = 0;
	g_data.start = 0;
	g_data.end = 0;
	g_data.high = 1;
	close_fd();
	if (i < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}
