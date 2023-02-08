#!/bin/zsh

#testing minishell

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing export builtin ${RESET}"

exec_test 0 \
'
export var="a b c"
echo $var
'
exec_test 1 \
'
export var=""
echo $var
'
exec_test 2 \
'
export var=""
echo $var
'
