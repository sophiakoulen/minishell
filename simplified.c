#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char	*line;

	if (isatty(2))
		rl_outstream = stderr;
	else if (isatty(1))
		rl_outstream = stdout;

	while (1)
	{
		if (isatty(0) && isatty(2))
			line = readline("prompt> ");
		else
			line = readline("");
		if (!line)
			break ;
		free(line);
	}
	return (0);
}
