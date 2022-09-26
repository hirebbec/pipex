/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:26:30 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/07 20:17:04 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

void	std_fd_swap(int argc, char **argv, t_data *data, char **envp)
{
	data->in = open(argv[1], O_RDONLY);
	if (data->in < 0)
		file_error(argv[1]);
	data->out = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (data->out < 0)
		file_error(argv[argc - 1]);
	data->check = dup2(data->in, 0);
	if (data->check < 0)
		exit(1);
	data->check = dup2(data->out, 1);
	if (data->check < 0)
		exit(1);
	data->count = 0;
	data->pwd = get_pwd(envp);
}

void	child_bonus(int	*fd, char **envp, char **argv, t_data *data)
{
	char	*path;
	char	**cmd_args;

	close(fd[0]);
	close(data->tmp[1]);
	if (dup2(fd[1], 1) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	close(fd[1]);
	if (dup2(data->tmp[0], 0) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	close(data->tmp[0]);
	cmd_args = ft_split(argv[3], ' ');
	if (access(get_cmd(argv[3]), X_OK) == 0)
		execve(get_cmd(argv[3]), cmd_args, envp);
	path = get_path(envp, argv[3], data->pwd);
	execve(path, cmd_args, envp);
	exit(0);
}

void	parent_bonus(int *fd, char **envp, char **argv, char *pwd)
{
	int		out;
	char	*path;
	char	**cmd_args;

	out = open(argv[5], O_RDWR | O_APPEND | O_CREAT, 0644);
	if (out < 0)
		file_error(argv[5]);
	close(fd[1]);
	if (dup2(fd[0], 0) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	close(fd[0]);
	if (dup2(out, 1) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	cmd_args = ft_split(argv[4], ' ');
	if (access(get_cmd(argv[4]), X_OK) == 0)
		execve(get_cmd(argv[4]), cmd_args, envp);
	path = get_path(envp, argv[4], pwd);
	if (execve(path, cmd_args, envp) == -1)
		exit(1);
}
