/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:11:14 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 20:16:25 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(char **argv, char *input, char *output, int cmd_count)
{
	t_pipex	*pipex;

	pipex = NULL;
	pipex = (t_pipex *)ppx_calloc(pipex, 1, sizeof(t_pipex));
	pipex -> here_doc = 0;
	if (!ft_strcmp(input, "here_doc"))
	{
		pipex -> here_doc = 1;
		fill_heredoc(pipex, argv[2]);
		cmd_count--;
	}
	else
		pipex -> input = open(input, O_RDONLY);
	if (pipex -> input < 0)
		perror("pipex: input");
	if (!ft_strcmp(input, "here_doc"))
		pipex -> output = open(output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		pipex -> output = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex -> output < 0)
		perror("pipex: output");
	pipex -> pid = ppx_calloc(pipex, cmd_count + 1, sizeof(pid_t));
	pipex -> pipe = ppx_calloc(pipex, cmd_count, sizeof(int) * 2);
	pipex -> commands_count = cmd_count;
	return (pipex);
}

void	close_and_wait(t_pipex *pipex, int argc, int *status)
{
	int	i;

	i = 1;
	while (++i < argc - 1)
	{
		close(pipex -> pipe[i - 2][READ_END]);
		close(pipex -> pipe[i - 2][WRITE_END]);
	}
	i = 1;
	while (++i < argc)
		waitpid(pipex -> pid[i - 2], status, 0);
	close(pipex -> input);
	close(pipex -> output);
	if (pipex -> here_doc)
		unlink("here_doc");
}

void	*ppx_calloc(t_pipex *pipex, int count, int size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		exit_free(pipex, EXIT_FAILURE);
	return (ptr);
}
