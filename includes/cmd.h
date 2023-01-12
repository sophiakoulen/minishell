#ifndef CMD_H
# define CMD_H

typedef	struct s_input_redir
{
	char	*str;
	int		is_heredoc;
}	t_input_redir;

typedef struct s_output_redir
{
	char	*str;
	int		is_append;
}	t_output_redir;

typedef struct s_cmd
{
	char			**args;
	t_input_redir	in;
	t_output_redir	out;
}	t_cmd;

#endif