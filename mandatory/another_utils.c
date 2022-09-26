/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:38:12 by hirebbec          #+#    #+#             */
/*   Updated: 2022/03/07 17:22:13 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../pipex.h"

void	cmd_error(char *cmd)
{
	write(2, "Command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}
