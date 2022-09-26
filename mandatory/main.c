/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:40:12 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/07 17:23:31 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	*pwd;

	if (argc != 5)
		error_msg("Wrong number of arguments\n");
	pwd = get_pwd(envp);
	check_cmds(argv, envp, pwd, argc);
	if (pipe(fd) < 0)
		error_msg("Problems with pipe, bad news(\n");
	pid = fork();
	if (pid < 0)
		error_msg("Problems with fork, very bad(\n");
	else if (pid == 0)
		child(fd, envp, argv, pwd);
	else if (pid > 0)
		parent(fd, envp, argv, pwd);
}

void	child(int	*fd, char **envp, char **argv, char *pwd)
{
	int		in;
	char	*path;
	char	**cmd_args;

	in = open(argv[1], O_RDONLY);
	if (in < 0)
		file_error(argv[1]);
	close(fd[0]);
	if (dup2(fd[1], 1) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	close(fd[1]);
	if (dup2(in, 0) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	cmd_args = ft_split(argv[2], ' ');
	if (access(get_cmd(argv[2]), X_OK) == 0)
		execve(get_cmd(argv[2]), cmd_args, envp);
	path = get_path(envp, argv[2], pwd);
	execve(path, cmd_args, envp);
}

void	parent(int *fd, char **envp, char **argv, char *pwd)
{
	int		out;
	char	*path;
	char	**cmd_args;

	wait(0);
	out = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (out < 0)
		file_error(argv[4]);
	close(fd[1]);
	if (dup2(fd[0], 0) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	close(fd[0]);
	if (dup2(out, 1) < 0)
		error_msg("Problems with dup2, idk why -_-\n");
	cmd_args = ft_split(argv[3], ' ');
	if (access(get_cmd(argv[3]), X_OK) == 0)
		execve(get_cmd(argv[3]), cmd_args, envp);
	path = get_path(envp, argv[3], pwd);
	if (execve(path, cmd_args, envp) == -1)
		exit(1);
}

void	check_cmds(char **argv, char **envp, char *pwd, int argc)
{
	int		i;
	char	**paths;

	i = 0;
	paths = get_paths(envp);
	while (i < argc - 3)
	{
		if (check_cmd(get_cmd(argv[i + 2]), paths, pwd) == -1)
			cmd_error(argv[i + 2]);
		i++;
	}
}

int	check_cmd(char *cmd, char **paths, char *pwd)
{
	int	i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (0);
	if (paths)
	{
		while (paths[i])
		{
			if (access(ft_strjoin(paths[i], ft_strjoin("/", cmd)), X_OK) == 0)
				return (0);
			i++;
		}
	}
	if (access(ft_strjoin(pwd, ft_strjoin("/", cmd)), X_OK) == 0)
		return (0);
	return (-1);
}
