/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:51:46 by marvin            #+#    #+#             */
/*   Updated: 2022/03/10 18:30:43 by hirebbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_data
{
	int		out;
	int		in;
	int		fd[2];
	int		count;
	int		check;
	int		pid;
	char	*pwd;
	char	*name;
	int		tmp[2];
}	t_data;

//
//INCLUDES
//
char	**ft_split(char *s, char c);
char	*ft_substr(char *s, int start, size_t len);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, int n);
void	putstr_fd(int fd, char *str);
void	putchar_fd(int fd, char c);
void	error_msg(char *msg);
void	file_error(char *name);
void	cmd_error(char *cmd);
//
//MANDATORY
//
char	*get_path(char **envp, char *cmd, char *pwd);
char	*ft_strjoin(char *s1, char *s2);
char	*get_local_path(char **envp);
void	free_mat(char **mat);
char	*get_cmd(char *command);
void	parent(int *fd, char **envp, char **argv, char *pwd);
void	child(int	*fd, char **envp, char **argv, char *pwd);
char	**get_paths(char **envp);
char	*get_pwd(char **envp);
//
//BONUS
//
void	std_fd_swap(int argc, char **argv, t_data *data, char **envp);
void	child_call(t_data *data, char **argv, char **envp);
void	parent_call(t_data *data);
void	last_cmd(t_data *data, char **argv, char **envp);
int		check_cmd(char *cmd, char **paths, char *pwd);
void	check_cmds(char **argv, char **envp, char *pwd, int argc);
//
//HERE_DOC
//
void	here_doc(int argc, char **argv, char **envp);
void	preparation(t_data *data);
void	reading(t_data *data, char *stop);
char	*charjoin(char *str, char c);
int		check(char *str, char *stop);
void	child_bonus(int	*fd, char **envp, char **argv, t_data *data);
void	parent_bonus(int *fd, char **envp, char **argv, char *pwd);
void	writing(char *str, t_data *data);
void	ft_check(char **envp, t_data *data, char **argv);
#endif