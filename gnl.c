/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 19:30:27 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 21:20:23 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	gnl_next(char **line)
{
	if (!(**line))
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_code);
	}
	else
	{
		ft_putstr_fd(*line, 1);
		return (1);
	}
}

static int	gnl_utils(int fd, char buff[2], char **line, char *tmp)
{
	int ret;

	while ((ret = read(fd, buff, 1)) >= 0)
	{
		if (!buff[0])
			return (gnl_next(line));
		else if (buff[0] != '\n')
		{
			if (ret > 0)
			{
				tmp = *line;
				*line = ft_strjoin(*line, buff);
				free(tmp);
			}
		}
		else
			return (1);
	}
	return (1);
}

int			get_next_line2(int fd, char **line)
{
	char		buff[2];
	char		*tmp;

	tmp = NULL;
	buff[0] = 0;
	buff[1] = 0;
	*line = ft_calloc(sizeof(char), 1);
	return (gnl_utils(fd, buff, line, tmp));
}
