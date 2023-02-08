#!/bin/zsh

#function testing for minishell

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing issues ${RESET}"

#107 and #83
exec_stderr 0 \
'
exit | cat | exit
echo $?
'
 #93
exec_stdout 1 'echo $ $ $'
exec_stdout 2 'echo $lasdjas'
exec_stdout 2 'echo $USER'
