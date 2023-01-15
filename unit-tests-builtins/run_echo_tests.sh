#!/bin/zsh
# Tokenizer unit test

source ../unit-tests/unit_test_framework.sh

N=echo

make $N
echo "\n${ITALIC}${YELLOW}Testing the parser${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 'echo_single' 'echo_single'
exec_test $N 1 'echoing two_strings' 'echoing' 'two_strings'
exec_test $N 2 'echoing three strings' 'echoing' 'three' 'strings'
# exec_test $N 4 '' ''
# exec_test $N 5 'do_a' 'newline
# there'
# exec_test $N 6 '-n' 'no_new_line
# '
# exec_test $N 7 '-n '
# '


# ./parsing.test 'echo hello | cat -e | new_test'


# exec_test 0 'echo hello | cat -e' '{echo hello  |  cat -e}'