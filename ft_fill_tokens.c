/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:21:16 by smago             #+#    #+#             */
/*   Updated: 2020/12/23 22:46:13 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_token2_0(char *str, char *str1)
{
	char *str2;
	char *str3;

	if (g_data.start != g_data.end)
	{
		str2 = ft_substr(str, g_data.start, g_data.end - g_data.start);
		str3 = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
		str1 = str3;
		g_data.start = g_data.end;
	}
	return (str1);
}

char	*fill_token2(char *str, char *str1)
{
	char *str2;
	char *str3;

	str1 = fill_token2_0(str, str1);
	if (str[g_data.end + 1] != '\0')
		g_data.end++;
	str2 = ft_calloc(sizeof(char), 2);
	str2[0] = str[g_data.end++];
	str3 = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	g_data.start = g_data.end;
	return (str3);
}

char	*fill_token3_0(char *str, char *str1)
{
	char c;

	c = str[g_data.end++];
	g_data.start = g_data.end;
	while (str[g_data.end] != c)
	{
		if (str[g_data.end] == '\\' && c == '\"')
			str1 = fill_token2(str, str1);
		else if (str[g_data.end] == '$' && c == '\"')
			str1 = ft_variable_env(str, str1);
		else
			g_data.end++;
	}
	str1 = fill_token2_0(str, str1);
	g_data.start = ++(g_data.end);
	return (str1);
}

char	*fill_token3(char *str)
{
	char *str1;

	str1 = ft_calloc(sizeof(char), 2);
	while (str[g_data.end] != '\0' && ft_strchr(("<>| \t"), \
			str[g_data.end]) == NULL)
	{
		if (str[g_data.end] == '\\')
		{
			str1 = fill_token2(str, str1);
		}
		else if (str[g_data.end] == '\"' || str[g_data.end] == '\'')
			str1 = fill_token3_0(str, str1);
		while (str[g_data.end] != '\0' && ft_strchr(("<>| \t \\ \' \""), \
				str[g_data.end]) == NULL)
		{
			if (str[g_data.end] == '$')
				str1 = ft_variable_env(str, str1);
			else
				g_data.end++;
		}
		str1 = fill_token2_0(str, str1);
	}
	return (str1);
}
