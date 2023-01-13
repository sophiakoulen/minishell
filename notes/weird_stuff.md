# weird stuff in bash

`<<EOF ` is OK: it does the heredoc thing and doesn't execute any command
Hypothesis: A child process and a corresponding heredoc pipe is launched.
This means we can have child processes that do not launch any commands.