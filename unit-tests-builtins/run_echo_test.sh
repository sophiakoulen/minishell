#!/bin/zsh
# Tokenizer unit test

source ../unit-tests/unit_test_framework.sh

N=echo

make $N
echo "\n${ITALIC}${YELLOW}Testing $N builtin${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 'echo_single' 'echo_single'
exec_test $N 1 'echoing two_strings' 'echoing' 'two_strings'
exec_test $N 2 'echoing three strings' 'echoing' 'three' 'strings'
exec_test $N 4 '' ''
# not sure how to test this with bash!
exec_test $N 5 'no_new_line' '-n' 'no_new_line'
exec_test $N 6 '' '-n'
exec_test $N 7 '-n   word' '-n  ' 'word'
exec_test $N 8 'word' '-n' 'word'
exec_test $N 9 'word' '-n' 'word'
exec_test $N 10 'word' '-nnnnnn' 'word'
exec_test $N 11 '-nnnnnn1 word' '-nnnnnn1' 'word'
exec_test $N 12 '-nnn1nnn word' '-nnn1nnn' 'word'
exec_test $N 13 '' '-nnn'
# ./parsing.test 'echo hello | cat -e | new_test'


# exec_test 0 'echo hello | cat -e' '{echo hello  |  cat -e}'
