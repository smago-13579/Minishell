/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:03:08 by smago             #+#    #+#             */
/*   Updated: 2020/12/24 18:45:42 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tmp_buffer(int len, int i)
{
	while (g_buf[len][++i])
	{
		free(g_buf[len][i]);
		g_buf[len][i] = NULL;
	}
}

void	ft_pipe2(int len)
{
	int pid;

	pipe(g_data.fd_p2);
	pid = fork();
	wait(NULL);
	if (pid < 0)
		print_error();
	else if (pid == 0)
	{
		close(g_data.fd_p2[0]);
		g_data.fd_p2[0] = -1;
		ft_built_or_exe(len, 0);
		exit(0);
	}
	close(g_data.fd_p[0]);
	g_data.fd_p[0] = -1;
	dup2(g_data.fd_tmp, 0);
	close(g_data.fd_tmp);
	close_fd();
	g_data.fd_error = 1;
	close(g_data.fd_p2[1]);
	g_data.fd_p2[1] = -1;
	g_data.fd_tmp = dup(0);
	dup2(g_data.fd_p2[0], 0);
}

void	ft_pipe1(void)
{
	if (g_data.fd_p2[0] >= 0)
	{
		close(g_data.fd_p2[0]);
		g_data.fd_p2[0] = -1;
		dup2(g_data.fd_tmp, 0);
		close(g_data.fd_tmp);
	}
	close_fd();
	g_data.fd_error = 1;
	close(g_data.fd_p[1]);
	g_data.fd_p[1] = -1;
	g_data.fd_tmp = dup(0);
	dup2(g_data.fd_p[0], 0);
}

void	ft_pipe(int len, int i)
{
	int	pid;

	if (g_data.fd_p[0] >= 0)
		ft_pipe2(len);
	else
	{
		pipe(g_data.fd_p);
		pid = fork();
		wait(NULL);
		if (pid < 0)
			print_error();
		else if (pid == 0)
		{
			close(g_data.fd_p[0]);
			g_data.fd_p[0] = -1;
			ft_built_or_exe(len, 0);
			exit(0);
		}
		ft_pipe1();
	}
	ft_free_tmp_buffer(len, i);
}
