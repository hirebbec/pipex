/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:20:19 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/07 17:24:37 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0 && \
		ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		here_doc(argc, argv, envp);
	if (argc < 5)
		error_msg("Wrong number of arguments\n");
	std_fd_swap(argc, argv, &data, envp);
	check_cmds(argv, envp, data.pwd, argc);
	while (data.count < argc - 4)
	{
		if (pipe(data.fd) < 0)
			error_msg("Problems with pipe, bad news(\n");
		data.pid = fork();
		if (data.pid < 0)
			error_msg("Problems with fork, very bad(\n");
		else if (data.pid == 0)
			child_call(&data, argv, envp);
		else if (data.pid > 0)
			parent_call(&data);
	}
	last_cmd(&data, argv, envp);
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
	int		i;
	char	*str;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (0);
	while (paths[i])
	{
		str = ft_strjoin(paths[i], ft_strjoin("/", cmd));
		if (access(str, X_OK) == 0)
		{
			free(str);
			return (0);
		}
		free(str);
		i++;
	}
	str = ft_strjoin(pwd, ft_strjoin("/", cmd));
	if (access(str, X_OK) == 0)
	{
		free(str);
		return (0);
	}
	free(str);
	return (-1);
}
