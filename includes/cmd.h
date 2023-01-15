#ifndef CMD_H
# define CMD_H

/*
	t_cmd is the basic command structure that contains the information needed
	by the pipeline execution stage.

	The parsing / input-processing stage needs to extract this information,
	in the form of a t_cmd array or linked list.

	cmd.args is the argument array, the first being the name of the command, the rest
	being the arguments, as we need to pass to the execve function.

	cmd.in is info about the input redirection:
		The input redirection is the last item from a cmd in the form
		`< WORD` or `<< WORD`.
		in.str is the corresponding WORD.
		in.type to know whether input from file or heredoc

	cmd.out is info about the output redirection:
		The output redirection is the last item in the form
		`> WORD` or `>> WORD`.
		out.str is the WORD.
		out.type to know whether append mode or not.
*/

#define INFILE 0
#define HEREDOC 1
#define OUTFILE 2
#define APPEND 3

typedef	struct s_redir
{
	int		type; //change this to enum later to avoid mistakes
	char	*str;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_redir	*in;
	t_redir	*out;
}	t_cmd;

#endif
