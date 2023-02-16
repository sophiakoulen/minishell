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

#64
exec_stdout 3 \
"
export U1='hello\"world'
env | grep U1
"
exec_stdout 4 \
"
export U2="'hello world'"
env | grep U2
"
exec_stdout 5 \
"
export U3='\"hello world\"'
env | grep U3
"
