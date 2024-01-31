/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 06:02:16 by bluzi             #+#    #+#             */
/*   Updated: 2023/05/05 20:22:48 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**pipex_split(t_pipex *pipex, char *cmd, int word_count)
{
	char	**split_cmd;
	int		i;
	int		j;

	i = 0;
	split_cmd = ppx_calloc(pipex, word_count + 1, sizeof(char *));
	while (*cmd)
	{
		if (get_quoted_content(pipex, &cmd, &split_cmd[i], i))
			i++;
		else if (isspace(*cmd))
			cmd++;
		else
		{
			j = 0;
			while (cmd[j] && !(cmd[j] == '\'' && \
				ft_strchr_pipex(cmd + j + 1, '\'')) && !(cmd[j] == '\"' && \
				ft_strchr_pipex(cmd + j + 1, '\"')) && !isspace(cmd[j]))
				j++;
			split_cmd[i++] = ft_strndup(pipex, cmd, j + 1);
			cmd += j;
		}
	}
	split_cmd[i] = NULL;
	return (split_cmd);
}

char	*ft_strndup(t_pipex *pipex, char *string, int length)
{
	char	*new_string;

	new_string = ppx_calloc(pipex, length + 1, sizeof(char));
	return (ft_strlcpy(new_string, string, length), new_string);
}

char	*ft_strchr_pipex(char *s, char c)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c && (i == 0 || s[i - 1] != '\\'))
			return (s + i);
		i++;
	}
	return (NULL);
}

int	quote_check(char **cmd)
{
	if (**cmd == '\'' && ft_strchr(*cmd + 1, '\''))
	{
		*cmd = ft_strchr(*cmd + 1, **cmd) + 1;
		return (1);
	}
	else if (**cmd == '\"' && ft_strchr(*cmd + 1, '\"'))
	{
		*cmd = ft_strchr(*cmd + 1, **cmd) + 1;
		return (1);
	}
	else
		return (0);
}

int	get_quoted_content(t_pipex *pipex, char **cmd, char **split_cmd, int i)
{
	if (i == 0 || *(*cmd - 1) != '\\')
	{	
		if (**cmd == '\'' && ft_strchr_pipex(*cmd + 1, '\''))
		{
			*split_cmd = ft_strdup_pipex(pipex, *cmd + 1, **cmd);
			*cmd = ft_strchr_pipex(*cmd + 1, **cmd) + 1;
			return (1);
		}
		else if (**cmd == '\"' && ft_strchr_pipex(*cmd + 1, '\"'))
		{
			*split_cmd = ft_strdup_pipex(pipex, *cmd + 1, **cmd);
			*cmd = ft_strchr_pipex(*cmd + 1, **cmd) + 1;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}
