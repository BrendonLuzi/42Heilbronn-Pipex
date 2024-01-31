/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:38:05 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 21:11:13 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		status;
	int		n;

	if (argc < 5)
		exit(EINVAL);
	n = 1;
	status = 0;
	pipex = init_pipex(argv, argv[1], argv[argc - 1], argc - 3);
	pipex -> paths = get_paths(pipex, envp);
	pipex -> commands = get_commands(pipex, argv, pipex -> commands_count, \
		pipex -> here_doc);
	while (++n < argc - 1 - pipex -> here_doc)
	{
		pipex -> pipe[n - 2] = ppx_calloc(pipex, 2, sizeof(int));
		pipex -> alloc_pipe_count = n - 1;
		if (n < argc - 2 - pipex -> here_doc)
			pipe(pipex -> pipe[n - 2]);
		pipex -> pid[n - 2] = fork();
		child(pipex, pipex -> commands, n - 2, envp);
	}
	close_and_wait(pipex, argc - pipex -> here_doc, &status);
	if (WIFEXITED(status))
		exit_free(pipex, WEXITSTATUS(status));
}
