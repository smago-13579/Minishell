/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smago <smago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:00:56 by smago             #+#    #+#             */
/*   Updated: 2020/12/28 21:38:12 by smago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

char			**g_envi;
char			***g_buf;
unsigned int	g_code;

typedef struct	s_data
{
	int			high;
	int			mid;
	int			start;
	int			end;
	int			fd[2];
	int			fd_p[2];
	int			fd_p2[2];
	int			fd_tmp;
	int			tmp_fd;
	int			fd_error;
}				t_data;
t_data	g_data;

void			ft_prompt0(void);
void			ft_prompt1(void);
int				ft_error_message(void);
void			ft_init(int ac, char **av, char **envp);
int				ft_parse(char **str);
int				ft_null_str(char *str);
char			*ft_spaces(char *str);
int				ft_new_buff(char *str);
char			*ft_quotes(char *str);
char			*fill_token2_0(char *str, char *str1);
char			*fill_token3(char *str);
int				ft_redirect(char *str);
char			*ft_variable_env(char *str, char *str1);
void			free_str(char **str1, char **str2);
void			free_all(char *str1, char *str2);
int				lexical(char *str);
void			ft_error(int i);
void			close_fd(void);
void			print_error(void);
void			redirect_error(void);
void			close_pipe(void);
int				ft_built_or_exe(int len, int i);
int				ft_exe_cmd(int len, int i);
int				ft_exe_cmd2(int len, int i);
void			ft_pipe(int len, int i);
int				ft_exit_code(int len, int i);
void			ft_exit_status(int status);

typedef struct	s_exp
{
	char		*key;
	char		*value;
}				t_exp;

t_exp			**g_exp;

void			ft_command_me(int i);
void			ft_export_sort(void);
void			ft_export_create(void);
void			ft_export_print(void);
void			ft_export_free(void);
t_exp			*ft_export_new_key(char *str);
int				ft_export_keys_cmp(t_exp *elem);
void			ft_unset(int i);
void			ft_export_delete(int i);
void			ft_export_add(int i);
t_exp			**ft_export_add2(int i, int count, int index);
void			ft_cd(int i, int j);
void			ft_echo(int i, int j);
void			ft_env(int j);
void			ft_pwd(void);
void			ft_g_envi_update(void);
void			ft_g_envi_print(void);
void			ft_add_oldpwd(void);
void			ft_add_pwd(void);
int				ft_oldpwd_index(void);
void			ft_cd_error(int i);
void			sig_handler(int signum);
int				get_next_line2(int fd, char **line);
void			ft_pwd_oldpwd_check(int *pwd, int *oldpwd);
int				ft_pwd_index(void);
void			ft_exe_error(int len, int i);
void			ft_fork_parent(int pid, int len, int i);
void			sig_handler3(int signum);

#endif
