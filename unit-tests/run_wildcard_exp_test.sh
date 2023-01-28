#!/bin/zsh
# Wildcard Expansion unit test

source unit_test_framework.sh

N=wildcard_exp

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

exec_test $N 0 "$(echo *)" '*'
# exec_test $N 1 "*.sh" '*.sh'
# exec_test $N 2 "run*" 'run*'
# exec_test $N 3 "*_*" '*_*'
# exec_test $N 4 "run*.sh" 'run*.sh'
# exec_test $N 5 "run*test*sh" 'run*test*sh'
