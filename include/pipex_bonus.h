/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:53:02 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 20:43:34 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <sys/wait.h>

# include "../lib/libft/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	int		input;
	int		output;
	int		here_doc;
	int		commands_count;
	int		alloc_pipe_count;
	int		**pipe;
	char	*argument;
	char	**paths;
	char	***commands;
	pid_t	*pid;
}	t_pipex;

//	generic start/end functions and protected pipex calloc
t_pipex	*init_pipex(char **argv, char *input, char *output, int cmd_count);
void	close_and_wait(t_pipex *pipex, int argc, int *status);
void	*ppx_calloc(t_pipex *pipex, int count, int size);

//	functions to parse the arguments and extract the commands
char	**get_paths(t_pipex *pipex, char *envp[]);
char	***get_commands(t_pipex *pipex, char *argv[], int cmds_num, int hd_mod);
char	*ft_strdup_pipex(t_pipex *pipex, char *string, char c);
size_t	ft_strlcpy_pipex(char *dst, const char *src, size_t dstsize);
int		cmd_word_count(char *argument);

//	pipex version of ft_split, handling quotation
char	**pipex_split(t_pipex *pipex, char *argument, int word_count);
char	*ft_strndup(t_pipex *pipex, char *string, int length);
char	*ft_strchr_pipex(char *s, char c);
int		quote_check(char **command);
int		get_quoted_content(t_pipex *pipex, char **cmd, char **split_cmd, int i);

//	functions needed by child process
void	child(t_pipex *pipex, char ***commands, int cmd_num, char *envp[]);
void	piping(t_pipex *pipex, int cmd_num);
char	*check_command(t_pipex *pipex, char *command, char **paths);
int		exist_and_exec(t_pipex *pipex, char *command, char free_command);

//	function to free and various free related utilities
void	free_pipex(t_pipex *pipex);
void	free_dblptr(char **ptr);
void	free_trplptr(char ***ptr);
char	*join_free(char *str1, char *str2);
void	exit_free(t_pipex *pipex, int exit_code);

//	functions handling heredoc
void	fill_heredoc(t_pipex *pipex, char *limiter);
int		ft_strcmp(char *s1, char *s2);

#endif