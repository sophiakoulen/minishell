#!/bin/zsh

#testing minishell

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing export builtin ${RESET}"

exec_stdout 0 \
'
export var="a b c"
echo $var
'
exec_stdout 1 \
'
export var=""
echo $var
'
exec_stdout 2 \
'
export var=""
echo $var
'
