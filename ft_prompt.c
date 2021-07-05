/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:35:34 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 16:50:49 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prompt0(void)
{
	ft_putstr_fd("minishell$ ", 1);
}

void	ft_prompt1(void)
{
	ft_putstr_fd("> ", 1);
}

int		ft_error_message(void)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	g_code = 2;
	return (0);
}
