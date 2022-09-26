/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:32:37 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/04 14:15:08 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

void	error_msg(char *msg)
{
	putstr_fd(2, msg);
	exit(1);
}

void	putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	putstr_fd(int fd, char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		putchar_fd(fd, str[i]);
		i++;
	}
}

void	file_error(char *name)
{
	write(2, "permission denied: ", 19);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
	exit(1);
}

char	*get_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PWD=", envp[i], 4))
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	return (ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4));
}
