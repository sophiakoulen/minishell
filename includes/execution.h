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
	int	*infile_fds;
	int	*outfile_fds;
}	t_fds;

/* heredoc */

void	do_single_heredoc(const char *delim, int fd);

/* find_cmd utils */

char	**extract_path(char **envp);
int		has_slashes(const char *str);
char	*concat_slash(const char *str1, const char *str2);
int		file_ok(char *filename, char **res);

/* find_cmd */

int		find_cmd(char **path, char *filename, char **res);

/* prepare cmd */

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n);
void		prepare_cmd(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n);

/* prepare fds */

t_fds	*prepare_fds(int n);
void	cleanup_fds(t_fds *fds, int n_cmds);

#endif