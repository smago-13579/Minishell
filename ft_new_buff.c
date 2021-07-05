/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:32:39 by smago             #+#    #+#             */
/*   Updated: 2021/01/04 15:01:21 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_tokens(char *str, int len)
{
	while (*str != '\0')
	{
		str = ft_spaces(str);
		if (ft_strchr("<>|", *str) != NULL)
		{
			if (*str == '>' && *(str + 1) == '>')
				str++;
			str++;
		}
		else if (*str != '\0')
		{
			while (*str != '\0' && ft_strchr(("<>| \t"), *str) == NULL)
			{
				if (*str == '\\' && *(str + 1) != '\0')
					str++;
				else if (*str == '\"' || *str == '\'')
					str = ft_quotes(str);
				str++;
			}
		}
		g_data.mid++;
	}
	if (!(g_buf[len] = (char **)ft_calloc(sizeof(char*), (g_data.mid + 1))))
		return (1);
	return (0);
}

void	fill_buffer2(char *str, int *len, int *i)
{
	if (ft_strchr("<>", str[g_data.end]) != NULL)
	{
		if (ft_redirect(str) < 0)
			redirect_error();
		(*i)--;
	}
	else if (str[g_data.end] == '|')
	{
		ft_pipe(*len, -1);
		*i = -1;
		g_data.end++;
		g_data.start = g_data.end;
	}
	else if (str[g_data.end] != '\0')
	{
		g_buf[*len][*i] = fill_token3(str);
	}
}

int		fill_buffer(char *str, int len, int i)
{
	while (i < g_data.mid)
	{
		while (str[g_data.end] == ' ' || str[g_data.end] == '\t')
		{
			g_data.end++;
			g_data.start = g_data.end;
		}
		ft_g_envi_update();
		fill_buffer2(str, &len, &i);
		i++;
	}
	ft_built_or_exe(len, 0);
	return (0);
}

int		ft_new_buff(char *str)
{
	int		len;

	len = 0;
	if (!(g_buf = (char ***)ft_calloc(sizeof(char**), (g_data.high + 1))))
		return (1);
	while (len < g_data.high)
	{
		if (count_tokens(str, len) == 1)
			return (1);
		fill_buffer(str, len, 0);
		if (++len < g_data.high)
			str = str + ft_strlen(str) + 1;
		g_data.mid = 0;
		g_data.start = 0;
		g_data.end = 0;
	}
	g_data.high = 1;
	return (0);
}
