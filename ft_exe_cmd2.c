/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:34:39 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 17:13:18 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute(int len, int i)
{
	char **av;

	while (g_buf[len][i])
		i++;
	av = (char**)ft_calloc(sizeof(char*), (i + 1));
	i = -1;
	while (g_buf[len][++i])
		av[i] = ft_strdup(g_buf[len][i]);
	if (g_data.fd[0] >= 0)
		dup2(g_data.fd[0], 0);
	if (g_data.fd[1] >= 0)
		dup2(g_data.fd[1], 1);
	else if (g_data.fd_p[1] >= 0)
		dup2(g_data.fd_p[1], 1);
	else if (g_data.fd_p2[1] >= 0)
		dup2(g_data.fd_p2[1], 1);
	execve(av[0], av, g_envi);
	close_fd();
	close_pipe();
	print_error();
	if (errno == 2)
		exit(127);
	else if (errno == 13)
		exit(126);
	exit(1);
}

int			ft_exe_cmd2(int len, int i)
{
	int pid;
	DIR	*dir;

	if ((dir = opendir(g_buf[len][i])))
	{
		closedir(dir);
		ft_exe_error(len, i);
		g_code = 126;
	}
	else
	{
		pid = fork();
		if (pid < 0)
			print_error();
		else if (pid == 0)
			ft_execute(len, i);
		else
			ft_fork_parent(pid, len, i);
	}
	close_fd();
	close_pipe();
	return (0);
}

void		ft_fork_parent(int pid, int len, int i)
{
	int	status;

	if (ft_strcmp(g_buf[len][i], "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sig_handler3);
		signal(SIGQUIT, sig_handler3);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	ft_exit_status(status);
}

void		ft_exe_error(int len, int i)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(g_buf[len][i], 2);
	ft_putstr_fd(": is a directory\n", 2);
}
