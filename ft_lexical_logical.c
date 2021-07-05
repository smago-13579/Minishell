/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexical_logical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:53:56 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 22:31:24 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexical3(char *str)
{
	if (*(str - 1) == ' ' || *(str - 1) == '\t')
	{
		if (*str == '>' || *str == '<')
			return (1);
	}
	if (*str == '<')
		return (1);
	if (*(str - 1) == '<' && *str == '>')
		return (1);
	if (*str == '>' && *(str + 1) == '>')
		return (1);
	return (0);
}

int	lexical2(char *str)
{
	if (*str == ';')
	{
		str++;
		str = ft_spaces(str);
		if (*str == ';' || *str == '|')
			return (1);
	}
	else if (*str == '|')
	{
		str++;
		str = ft_spaces(str);
		if (*str == ';' || *str == '|')
			return (1);
	}
	else
	{
		str++;
		str = ft_spaces(str);
		if (*str == '\0' || *str == '|' || *str == ';' || lexical3(str) == 1)
			return (1);
	}
	return (0);
}

int	lexical(char *str)
{
	str = ft_spaces(str);
	if (*str == '|' || *str == ';')
		return (ft_error_message());
	while (*str)
	{
		if (*str == '\\' && *(str + 1) != '\0')
			str += 2;
		else
		{
			if (*str == '\'' || *str == '\"')
			{
				if (!(str = ft_quotes(str)))
					return (0);
			}
			if (ft_strchr("<>|;", *str) != NULL)
			{
				if (lexical2(str))
					return (ft_error_message());
			}
			if (*str == '\0')
				return (1);
			str++;
		}
	}
	return (1);
}
