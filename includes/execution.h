#ifndef EXECUTION_H
# define EXECUTION_H

# include "cmd.h"

/*
	info we need during the execution phase.

	- input and output file descriptors we'll need to redirect to
	- full path of the command if it is found in PATH or already a path
	- status of the command. 0 means we can execute.
*/
typedef struct s_cmd_info
{
	int		i_fd;
	int		o_fd;
	char	*full_path;
	int		status;
}	t_cmd_info;

/*
	file descriptors we need during execution phase.

	- pipes : pipes to redirect a cmd's output into another cmd's input
	- hd_pipes : pipes to execute heredocs
	- infile_fds : file descriptors corresponding to input files
	- outfile_fds : file descriptors corresponding to output files.
*/
typedef struct s_fds
{
	int	**pipes;
	int	**hd_pipes;
	int	*infile_fds;
	int	*outfile_fds;
}	t_fds;

/* heredoc */

void	do_all_heredocs(t_cmd *cmds, int **hd_pipes, int n);

/* find_cmd utils */

char	**extract_path(char **envp);
int		has_slashes(const char *str);
char	*concat_slash(const char *str1, const char *str2);
int		file_ok(char *filename, char **res);

/* find_cmd */

int		find_cmd(char **path, char *filename, char **res);

/* prepare cmd */

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n);
void		cleanup_all_info(t_cmd_info *infos, int n);

/* prepare fds */

t_fds	*prepare_fds(int n);
void	cleanup_fds(t_fds *fds, int n_cmds);

/* exec_utils */

int		compute_return_value(int status);
int		redirect(int input_fd, int output_fd);
void	close_fds(t_fds *fds, int n);

/* multiple commands */

int	multiple_commands(t_cmd *cmds, t_fds *fds, int n);

#endif