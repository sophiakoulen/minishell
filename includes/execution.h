#ifndef EXECUTION_H
# define EXECUTION_H

# include "cmd.h"

typedef	struct s_pipeline
{
	int		n_cmds;
	t_cmd	*cmds;
}	t_pipeline;

typedef struct s_cmd_info
{
	int		i_fd;
	int		o_fd;
	int		status;
	char	*full_path;
}	t_cmd_info;

typedef struct s_fds
{
	int	**pipes;
	int	**hd_pipes;
}	t_fds;

/* heredoc */

void	do_single_heredoc(const char *delim, int fd);

#endif