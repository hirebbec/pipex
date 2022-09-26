/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:45:28 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/10 18:29:37 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

char	*charjoin(char *str, char c)
{
	int		i;
	char	*res;

	i = ft_strlen(str);
	res = malloc(i + 2);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

void	ft_check(char **envp, t_data *data, char **argv)
{
	char	**paths;

	paths = get_paths(envp);
	data->pwd = get_pwd(envp);
	if (check_cmd(get_cmd(argv[3]), paths, data->pwd) == -1)
		cmd_error(argv[3]);
	if (check_cmd(get_cmd(argv[4]), paths, data->pwd) == -1)
		cmd_error(argv[4]);
}
