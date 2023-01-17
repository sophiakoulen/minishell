#!/bin/zsh
# Tokenizer unit test

source ../unit-tests/unit_test_framework.sh

N=env

make $N
echo "\n${ITALIC}${YELLOW}Testing $N builtin${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 'env' '$(env)'
# ./parsing.test 'echo hello | cat -e | new_test'


# exec_test 0 'echo hello | cat -e' '{echo hello  |  cat -e}'
