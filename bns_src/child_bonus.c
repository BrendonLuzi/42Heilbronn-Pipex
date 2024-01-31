/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:15:22 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 21:12:20 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	piping(t_pipex *pipex, int cmd_num)
{
	int	fd_input;
	int	fd_output;

	if (cmd_num)
		fd_input = pipex -> pipe[cmd_num - 1][READ_END];
	else
		fd_input = pipex -> input;
	if (dup2(fd_input, STDIN_FILENO) < 0)
		exit_free(pipex, EXIT_FAILURE);
	if (pipex -> commands[cmd_num + 1])
		fd_output = pipex -> pipe[cmd_num][WRITE_END];
	else
		fd_output = pipex -> output;
	if (dup2(fd_output, STDOUT_FILENO) < 0)
		exit_free(pipex, EXIT_FAILURE);
	if (pipex -> commands[cmd_num + 1])
		cmd_num++;
	while (--cmd_num >= 0)
	{
		close(pipex -> pipe[cmd_num][READ_END]);
		close(pipex -> pipe[cmd_num][WRITE_END]);
	}
}

char	*check_command(t_pipex *pipex, char *command, char **paths)
{
	char	*new_command;

	if ((*command == '.' || ft_strchr(command, '/')) && \
		!ft_strchr(command, ' ') && !access(command, F_OK))
	{
		if (exist_and_exec(pipex, command, 0))
			return (command);
	}
	else
	{
		while (*paths)
		{
			new_command = ft_strjoin(*paths++, command);
			if (exist_and_exec(pipex, new_command, 1))
				return (new_command);
			free(new_command);
		}
		dup2(2, 1);
		ft_printf("pipex: %s: command not found\n", command);
		exit_free(pipex, 127);
	}
	return (NULL);
}

void	child(t_pipex *pipex, char ***commands, int cmd_num, char *envp[])
{
	int		status;
	char	*to_execute;

	if (!pipex -> pid[cmd_num])
	{
		piping(pipex, cmd_num);
		to_execute = check_command(pipex, commands[cmd_num][0], pipex -> paths);
		status = execve(to_execute, commands[cmd_num], envp);
		perror(NULL);
		exit_free(pipex, status);
	}
	else if (pipex -> pid[cmd_num] == -1)
	{
		perror(NULL);
		exit_free(pipex, EXIT_FAILURE);
	}
}

int	exist_and_exec(t_pipex *pipex, char *command, char free_command)
{
	if (!access(command, F_OK))
	{
		if (!access(command, X_OK))
			return (1);
		else
		{
			if (free_command)
				free(command);
			exit_free(pipex, 126);
		}
	}
	return (0);
}
