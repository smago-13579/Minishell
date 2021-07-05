/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:37:40 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 21:33:57 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_handler(int signum)
{
	if (signum == 2)
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		ft_prompt0();
		g_code = 1;
	}
	else if (signum == 3)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void		sig_handler3(int signum)
{
	if (signum == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	else if (signum == 2)
		ft_putchar_fd(10, 1);
}

int			main(int ac, char **av, char **envp)
{
	int		i;
	char	*line;

	i = 1;
	ft_init(ac, av, envp);
	ft_export_create();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (i)
	{
		ft_prompt0();
		i = get_next_line2(0, &line);
		if (ft_null_str(line))
		{
			ft_parse(&line);
		}
		free_all(line, NULL);
	}
	return (0);
}
