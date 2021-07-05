/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:45:13 by smago             #+#    #+#             */
/*   Updated: 2021/01/03 16:07:29 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_and_cmd(char *name, char *path)
{
	DIR				*dir;
	struct dirent	*pd;
	char			*str;
	char			*str1;

	if ((dir = opendir(path)))
	{
		while ((pd = readdir(dir)))
		{
			if (ft_strcmp(pd->d_name, name) == 0)
			{
				str1 = ft_strjoin(path, "/");
				str = ft_strjoin(str1, name);
				free(str1);
				closedir(dir);
				return (str);
			}
		}
	}
	closedir(dir);
	return (NULL);
}

char	*find_cmd(char *name, int i)
{
	char **path;
	char *str;

	while (g_envi[i] && ft_strncmp(g_envi[i], "PATH=", 5))
		i++;
	if (!g_envi[i])
		return (NULL);
	str = g_envi[i] + 5;
	path = ft_split(str, ':');
	str = NULL;
	i = 0;
	while (path[i] && !str)
	{
		str = path_and_cmd(name, path[i]);
		i++;
	}
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (str);
}

int		cmp_cmd(char *str, int len, int j)
{
	if (g_buf[len][0][j] != '/' && g_buf[len][0][j] != '.')
	{
		while (g_buf[len][0][j])
		{
			g_buf[len][0][j] = ft_tolower(g_buf[len][0][j]);
			j++;
		}
		str = g_buf[len][0];
		if (ft_strcmp(str, "echo") == 0)
			return (1);
		if (ft_strcmp(str, "cd") == 0)
			return (1);
		if (ft_strcmp(str, "pwd") == 0)
			return (1);
		if (ft_strcmp(str, "export") == 0)
			return (1);
		if (ft_strcmp(str, "unset") == 0)
			return (1);
		if (ft_strcmp(str, "env") == 0)
			return (1);
	}
	return (0);
}

int		ft_exe_cmd(int len, int i)
{
	char *str;
	char c;

	c = g_buf[len][i][0];
	if (ft_strcmp(g_buf[len][i], "exit") == 0)
		return (ft_exit_code(len, 0));
	else if (c != '/' && c != '.' && c != '\0')
	{
		if (!(str = find_cmd(g_buf[len][i], 0)))
		{
			close_fd();
			close_pipe();
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(g_buf[len][i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("command not found\n", 2);
			g_code = 127;
			return (0);
		}
		free(g_buf[len][i]);
		g_buf[len][i] = ft_strdup(str);
		free(str);
	}
	return (ft_exe_cmd2(len, 0));
}

int		ft_built_or_exe(int len, int i)
{
	int tmp;

	if (g_buf[len][i] && g_data.mid > 0 && g_data.fd_error > 0)
	{
		if (cmp_cmd(g_buf[len][i], len, 0) == 1)
		{
			tmp = dup(1);
			if (g_data.fd[1] >= 0)
				dup2(g_data.fd[1], 1);
			else if (g_data.fd_p[1] >= 0)
				dup2(g_data.fd_p[1], 1);
			else if (g_data.fd_p2[1] >= 0)
				dup2(g_data.fd_p2[1], 1);
			ft_command_me(len);
			dup2(tmp, 1);
			close(tmp);
		}
		else
			ft_exe_cmd(len, i);
	}
	close_fd();
	close_pipe();
	g_data.fd_error = 1;
	return (0);
}
