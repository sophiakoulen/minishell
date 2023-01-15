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



#endif
