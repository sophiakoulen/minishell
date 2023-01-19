/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:11:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/19 13:09:22 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_redirs(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n);
static void prepare_cmd_path(t_cmd *cmd, t_cmd_info *info, char **path);
static void	prepare_cmd(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n, char **path);

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n, t_env *env)
{
	t_cmd_info	*infos;
	int			i;
	char		**path;
	char		**env_array;

	env_array = env_to_strarr(env);
	path = extract_path(env_array);
	//cleanup env_array
	infos = x_malloc(n, sizeof(*infos));
	i = 0;
	while (i < n)
	{
		prepare_cmd(&cmds[i], &infos[i], fds, i, n, path);
		i++;
	}
	//cleanup path
	return (infos);
}

void	cleanup_all_info(t_cmd_info *infos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(infos[i].full_path);
		i++;
	}
	free(infos);
}

static void	prepare_cmd(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n, char **path)
{
	info->status = 0;
	info->builtin = -1;
	info->i_fd = -1;
	info->o_fd = -1;
	info->full_path = 0;
	info->has_heredoc = 0;
	info->heredoc_delim = 0;
	prepare_redirs(cmd, info, fds, i, n);
	if (!info->status)
		prepare_cmd_path(cmd, info, path);
}

static void	prepare_redirs(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n)
{
	int		fdin;
	int		fdout;
	t_list	*lst;
	t_item	*redir;
	int		flags;

	/* default input */
	if (i == 0)
		fdin = STDIN_FILENO;
	else
		fdin = fds->pipes[i - 1][0];

	if (i == n - 1)
		fdout = STDOUT_FILENO;
	else
		fdout = fds->pipes[i][1];

	/* iterate over args list */
	lst = cmd->redirs;
	while (lst)
	{
		redir = lst->content;
		if (redir->modifier == e_infile)
		{
			fdin = open(redir->word, O_RDONLY);
			if (fdin < 0)
			{
				perror(redir->word); //later error printing needs to be done in child
				info->status = 1;
				break ;
			}
			fds->infile_fds[i] = fdin;
		}
		else if (redir->modifier == e_outfile)
		{
			flags = O_WRONLY | O_TRUNC | O_CREAT;
			fdout = open(redir->word, flags, 0644);
			if (fdout < 0)
			{
				perror(redir->word);
				info->status = 1;
				break ;
			}
			fds->outfile_fds[i] = fdout;
		}
		else if (redir->modifier == e_append)
		{
			flags = O_WRONLY | O_TRUNC | O_CREAT | O_APPEND;
			fdout = open(redir->word, flags, 0644);
			if (fdout < 0)
			{
				perror(redir->word);
				info->status = 1;
				break ;
			}
			fds->outfile_fds[i] = fdout;
		}
		else
		{
			info->has_heredoc = 1;
			info->heredoc_delim = redir->word;
			fdin = fds->hd_pipes[i][0];
		}
		lst = lst->next;
	}
	info->o_fd = fdout;
	info->i_fd = fdin;
}

static void prepare_cmd_path(t_cmd *cmd, t_cmd_info *info, char **path)
{
	if (cmd->args[0])
	{
		if (ret_builtin_enum(cmd->args[0]) != -1)
			info->builtin = ret_builtin_enum(cmd->args[0]);
		else
			info->status = find_cmd(path, cmd->args[0], &(info->full_path));
	}
}
