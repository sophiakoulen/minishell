#!/bin/zsh
# Tokenizer unit test

source unit_test_framework.sh

N=wildcard_exp

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

exec_test $N 0 "*.sh" '*.sh'
exec_test $N 1 "run*.sh" 'run*.sh'
exec_test $N 1 "run*test*sh" 'run*test*sh'
