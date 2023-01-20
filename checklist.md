# testing checklist

## prompt and input
- prompt is written in interactive mode only.
- readline functionality is working: cmd-a puts cursor at start of prompt

## history
- history doesn't contain empty lines
- optional: save history in file and load it when starting an interactve shell

## command finding
- commands are found in PATH variable
- if PATH is not set, a default PATH of "/usr/bin:/bin" is used
- if command is not found, error 127.
- if command is found but permission denied, "Permission denied" and error 126.
- if other error like "Too many symboloc links", error 126.
- if the command contains slashes, we do not look in PATH.

## quoting
- single quotes escape any meta-characters.
- double quotes escape any meta-characters except for variables.
- nested quotes: "hello'$world'" $world is expanded.

## redirections
- redirections are handled in order they are typed.
- even if not used, output files are opened.
- redirection handling stops at first problem (if first input file is broken, we do not look at second input file and do not look at following output files)
- variable expansion is not done in heredoc delimiters.
- the history is not updated with the lines from heredoc
- output file is truncated
- permission of output file is 0644
- error code when problem with input or output is 1.

## pipes
- parent waits for child process to finish (`sleep 10`).
- file redirections have priority over pipes
- the exit status is that of the last command

## expansion
- some word splitting is done after variable expansion
- meta characters in variable values are not interpreted except the wildcard.
- $? is substituted by the value of the last command
- if error is found during expansion, exit status is greater than 0, for example, 1.

## signal handling
- ctrl-C
- ctrl-D
- ctrl-\
  
## builtins
- redirections work with builtins (and the following lines)
- builtins work in pipelines
- builtins have priority over commands
- echo:
	- multiple arguments are printed
	- -n option is handled
	- if no argument, a newline is printed
- pwd:
	- absolute path of working directory is printed
	- error handling of getcwd()
	- in bash, no error when multiple arguments
- export:
	- with no arguments: prints variables sorted, specific format
	- handle multiple arguments
	- error when identifier contains invalid characters
- unset:
	- handle multiple arguments
	- nothing happens when no arguments
	- error when identifier contains invalid characters
- env:
	- env prints the variables environment variable and their values (no specific order)

## leaks
- check leaks during execution and at exit using Leaks

## malloc protection and system calls
- malloc failure doesn't make the shell crash
- all calls to open are protected

## syntax errors
- syntax error is generated when a quote is not closed
- syntax error is generated for invalid expressions
- all error messages are printed on stderr
- optional: error messages are printed in the corresponding child process
- error messages have the right prefix and "minishell: " prepended to them.
