/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:58:42 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/04 14:14:49 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

char	*get_path(char **envp, char *cmd, char *pwd)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*command;

	command = ft_strjoin(pwd, ft_strjoin("/", get_cmd(cmd)));
	if (access(command, X_OK) == 0)
		return (command);
	cmd = get_cmd(cmd);
	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char	*get_cmd(char *command)
{
	char	**mat;
	char	*str;

	mat = ft_split(command, ' ');
	str = ft_strdup(mat[0]);
	free_mat(mat);
	return (str);
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

char	*get_local_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
}

char	**get_paths(char **envp)
{
	char	*path;
	char	**paths;

	path = get_local_path(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free (path);
	return (paths);
}
