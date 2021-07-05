/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:18:35 by smago             #+#    #+#             */
/*   Updated: 2020/11/23 19:23:32 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char *str1, char *str2)
{
	int len;
	int x;

	free_str(&str1, &str2);
	len = 0;
	if (g_buf)
	{
		while (g_buf[len])
		{
			x = 0;
			while (g_buf[len][x])
			{
				free(g_buf[len][x]);
				x++;
			}
			free(g_buf[len]);
			len++;
		}
		free(g_buf);
		g_buf = NULL;
	}
}

void	free_str(char **str1, char **str2)
{
	if (*str1)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (*str2)
	{
		free(*str2);
		*str2 = NULL;
	}
}
