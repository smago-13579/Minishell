/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:50:40 by smago             #+#    #+#             */
/*   Updated: 2020/12/27 20:34:06 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(char *str)
{
	while (*str == ' ' || *str == '\t')
	{
		*str = '\0';
		str--;
	}
	if (*str == '|')
		return (1);
	return (0);
}

char		*ft_quotes(char *str)
{
	char c;

	c = *str++;
	while (*str && *str != c)
	{
		if (*str == '\\' && *(str + 1) != '\0' && c == '\"')
			str++;
		str++;
	}
	if (*str == '\0')
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (NULL);
	}
	return (str);
}

int			ft_parse2(char **str2)
{
	char	*str;

	str = *str2;
	while (*str)
	{
		if (*str == '\\' && *(str + 1) != '\0')
			str += 2;
		else
		{
			if (*str == '\'' || *str == '\"')
			{
				if (!(str = ft_quotes(str)))
					return (1);
			}
			if (*str == ';')
			{
				*str = '\0';
				g_data.high++;
			}
			str++;
		}
	}
	if (ft_new_buff(*str2) == 1)
		return (1);
	return (0);
}

int			ft_parse(char **str)
{
	char	*line;
	char	*str2;
	int		i;

	line = NULL;
	while ((i = lexical(*str)) && check_pipe(&(*str)[ft_strlen(*str) - 1]))
	{
		ft_prompt1();
		get_next_line2(0, &line);
		if (!(str2 = ft_strjoin(*str, line)))
		{
			free_str(str, &line);
			return (ft_null_str(str2));
		}
		free_str(str, &line);
		*str = str2;
	}
	if (i == 0 || ft_parse2(str) == 1)
		free_str(str, &line);
	return (0);
}
