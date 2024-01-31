/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:19:14 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 20:44:15 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_free(t_pipex *pipex, int exit_code)
{
	free_pipex(pipex);
	exit(exit_code);
}

void	free_dblptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_trplptr(char ***ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free_dblptr(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex)
	{	
		if (pipex -> pipe)
		{
			while (i < pipex -> alloc_pipe_count)
				free(pipex -> pipe[i++]);
			free(pipex -> pipe);
		}
		if (pipex -> pid)
			free(pipex -> pid);
		if (pipex -> argument)
			free(pipex -> argument);
		if (pipex -> paths)
			free_dblptr(pipex -> paths);
		if (pipex -> commands)
			free_trplptr(pipex -> commands);
		free(pipex);
	}
}

char	*join_free(char *str1, char *str2)
{
	char	*new_str;

	new_str = ft_strjoin(str1, str2);
	free(str1);
	return (new_str);
}
