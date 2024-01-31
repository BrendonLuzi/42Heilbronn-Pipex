/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:14:37 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 20:44:15 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	***get_commands(t_pipex *pipex, char *argv[], int cmds_num, int h_doc)
{
	char	***commands;
	int		i;

	commands = (char ***)ppx_calloc(pipex, cmds_num + 1, sizeof(char **));
	i = 0;
	while (i < cmds_num)
	{
		pipex -> argument = ft_strdup_pipex(pipex, argv[2 + i + h_doc], '\0');
		if (access(pipex -> argument, F_OK))
			commands[i] = pipex_split(pipex, argv[2 + i + h_doc], \
				cmd_word_count(argv[2 + i + h_doc]));
		else
		{
			commands[i] = ppx_calloc(pipex, 2, sizeof(char *));
			commands[i][0] = ft_strdup(pipex -> argument);
			commands[i][1] = NULL;
		}
		i++;
		free(pipex -> argument);
		pipex -> argument = NULL;
	}
	commands[cmds_num] = NULL;
	return (commands);
}

char	**get_paths(t_pipex *pipex, char *envp[])
{
	char	**paths;
	int		i;

	i = -1;
	paths = NULL;
	while (envp && envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	if (!envp || !(*envp) || !paths)
	{
		paths = ppx_calloc(pipex, 2, sizeof(char *));
		paths[0] = ppx_calloc(pipex, ft_strlen("/usr/bin") + 1, sizeof(char));
		ft_strlcpy(paths[0], "/usr/bin", ft_strlen("/usr/bin") + 1);
		paths[1] = NULL;
	}
	i = -1;
	while (paths[++i])
		paths[i] = join_free(paths[i], "/");
	return (paths);
}

char	*ft_strdup_pipex(t_pipex *pipex, char *string, char c)
{
	char	*new_string;
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (string[i])
	{
		if (string[i] == c)
		{
			length++;
			break ;
		}
		if (string[i] == '\\')
			i++;
		i++;
		length++;
	}
	if (c == '\0')
		length++;
	new_string = ppx_calloc(pipex, length + 1, sizeof(char));
	return (ft_strlcpy_pipex(new_string, string, length), new_string);
}

size_t	ft_strlcpy_pipex(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	j = 0;
	while (i < dstsize - 1 && src[j])
	{
		if (src[j] == '\\')
			j++;
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	cmd_word_count(char *cmd)
{
	int	count;

	if (*cmd && !isspace(*cmd) && *cmd != '\'' && *cmd != '\"')
		count = 1;
	else
		count = 0;
	while (*cmd)
	{
		if (quote_check(&cmd))
			count++;
		else if (isspace(*cmd))
		{
			while (isspace(*cmd))
				cmd++;
		}
		else
		{
			if (*(cmd - 1) == '\'' || *(cmd - 1) == '\"' || isspace(*(cmd - 1)))
				count++;
			cmd++;
		}
	}
	return (count);
}
