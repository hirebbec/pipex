/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:43:19 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/10 18:31:08 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

void	here_doc(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 6)
		error_msg("Wrong number of arguments\n");
	preparation(&data);
	reading(&data, argv[2]);
	ft_check(envp, &data, argv);
	if (pipe(data.fd) < 0)
		error_msg("Problems with pipe, bad news(\n");
	data.pid = fork();
	if (data.pid < 0)
		error_msg("Problems with fork, very bad(\n");
	else if (data.pid == 0)
		child_bonus(data.fd, envp, argv, &data);
	else
	{
		close(data.tmp[0]);
		close(data.tmp[1]);
		parent_bonus(data.fd, envp, argv, data.pwd);
	}
}

void	preparation(t_data *data)
{
	if (pipe(data->tmp) < 0)
		error_msg("Problems with pipe, bad news(\n");
}

void	reading(t_data *data, char *stop)
{
	char	c;
	char	*str;
	int		i;

	i = 0;
	str = "";
	write(1, "pipe heredoc> ", 15);
	while (1)
	{
		read(0, &c, 1);
		str = charjoin(str, c);
		if (c == '\n')
		{
			if (check(str, stop) == 0)
				break ;
			else
				write(1, "pipe heredoc> ", 15);
		}
	}
	str = ft_substr(str, 0, ft_strlen(str) - ft_strlen(stop) - 1);
	data->pid = fork();
	if (data->pid < 0)
		error_msg("Problems with fork, very bad(\n");
	else if (data->pid == 0)
		writing(str, data);
}

int	check(char *str, char *stop)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_split(str, '\n');
	while (res[i + 1])
		i++;
	if (ft_strncmp(res[i], stop, ft_strlen(res[i])) == 0 && \
		ft_strncmp(res[i], stop, ft_strlen(stop)) == 0)
		return (0);
	return (1);
}

void	writing(char *str, t_data *data)
{
	int	i;

	i = 0;
	close(data->tmp[0]);
	while (str[i])
	{
		write(data->tmp[1], &str[i], 1);
		i++;
	}
	exit(0);
}
