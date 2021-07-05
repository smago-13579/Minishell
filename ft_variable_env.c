/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:56:58 by smago             #+#    #+#             */
/*   Updated: 2020/12/27 17:30:14 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_envi(char *str1, char *str2, char *envi)
{
	int		len;
	int		end;
	char	*str3;

	len = 0;
	end = 0;
	str3 = NULL;
	while (envi[len] != '=')
		len++;
	while (envi[end])
		end++;
	if (ft_strncmp(envi, str2, len) == 0 && len == (int)ft_strlen(str2))
	{
		len++;
		free(str2);
		str2 = ft_substr(envi, len, end - len);
		str3 = ft_strjoin(str1, str2);
		free(str2);
		free(str1);
	}
	return (str3);
}

char	*ft_variable_exit(char *str1, char *str2, char *str3)
{
	if (str3 != NULL)
		return (str3);
	if (ft_strcmp(str2, "?") == 0)
	{
		free(str2);
		str2 = ft_itoa((int)g_code);
		str3 = ft_strjoin(str1, str2);
		free(str2);
		free(str1);
	}
	return (str3);
}

char	*ft_variable_env(char *str, char *str1)
{
	char	*str2;
	char	*str3;
	int		i;

	i = 0;
	str1 = fill_token2_0(str, str1);
	g_data.start = ++g_data.end;
	while (str[g_data.end] != '\0' && ft_strchr(("<>|$ \t \\ \' \"/"), \
		str[g_data.end]) == NULL)
		g_data.end++;
	str2 = ft_substr(str, g_data.start, g_data.end - g_data.start);
	while (g_envi[i] && !(str3 = ft_str_envi(str1, str2, g_envi[i])))
	{
		i++;
	}
	str3 = ft_variable_exit(str1, str2, str3);
	g_data.start = g_data.end;
	if (str3 == NULL)
	{
		free(str2);
		return (str1);
	}
	return (str3);
}
