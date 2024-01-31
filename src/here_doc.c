/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 04:03:08 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 20:15:16 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_heredoc(t_pipex *pipex, char *limiter)
{
	char	*line;

	pipex -> input = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_printf("heredoc>");
		line = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(line, limiter))
			break ;
		write(pipex -> input, line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limiter);
	close(pipex -> input);
	pipex -> input = open("here_doc", O_RDONLY, 0644);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
