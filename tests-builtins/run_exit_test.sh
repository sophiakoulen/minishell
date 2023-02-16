#!/bin/zsh
# Exit builtin unit test

source ../tests-unit/unit_test_framework.sh

N=exit

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 '{echo} | {{test} | {cat{-e}}}' 'echo | test | cat -e'


# ./parsing.test 'echo hello | cat -e | new_test'


# exec_test 0 'echo hello | cat -e' '{echo hello  |  cat -e}'
