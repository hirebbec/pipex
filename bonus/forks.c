/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:38:15 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/07 18:23:09 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

void	child_call(t_data *data, char **argv, char **envp)
{
	char	*path;
	char	**cmd_argc;

	if (dup2(data->fd[1], 1) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	close(data->fd[1]);
	close(data->fd[0]);
	cmd_argc = ft_split(argv[data->count + 2], ' ');
	if (access(get_cmd(argv[data->count + 2]), X_OK) == 0)
		execve(get_cmd(argv[data->count + 2]), cmd_argc, envp);
	path = get_path(envp, argv[data->count + 2], data->pwd);
	execve(path, cmd_argc, envp);
	exit(0);
}

void	parent_call(t_data *data)
{
	if (dup2(data->fd[0], 0) < 0)
		error_msg("Problems with fork, very bad(\n");
	close(data->fd[0]);
	close(data->fd[1]);
	data->count++;
}

void	last_cmd(t_data *data, char **argv, char **envp)
{
	char	*path;
	char	**cmd_argc;

	data->pid = fork();
	if (data->pid < 0)
		error_msg("Problems with fork, very bad(\n");
	else if (data->pid == 0)
	{
		if (dup2(data->out, 1) < 0)
			error_msg("Problems with dup2, idk why -_-\n");
		close(data->out);
		cmd_argc = ft_split(argv[data->count + 2], ' ');
		if (access(get_cmd(argv[data->count + 2]), X_OK) == 0)
			execve(get_cmd(argv[data->count + 2]), cmd_argc, envp);
		path = get_path(envp, argv[data->count + 2], data->pwd);
		execve(path, cmd_argc, envp);
	}
}
