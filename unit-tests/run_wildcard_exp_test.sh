#!/bin/zsh
# Wildcard Expansion unit test

source unit_test_framework.sh

N=wildcard_exp

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>


exec_test $N 0 "$(echo *) " '*'
exec_test $N 1 "$(echo *.sh) " '*.sh'
exec_test $N 2 "$(echo run*) " 'run*'
exec_test $N 3 "$(echo *_*) " '*_*'
exec_test $N 4 "$(echo run*.sh) " 'run*.sh'
exec_test $N 5 "$(echo run*test*sh) " 'run*test*sh'
exec_test $N 6 "$(echo test*) " 'test*'
exec_test $N 7 "$(echo file) " 'file'
exec_test $N 8 "$(echo *file) " '*file'
exec_test $N 8 "$(echo .*) " '.*'

exec_test $N 10 "$(echo *M*) " '*M*'


touch apple apple1 apple2 apple3 applebananna bannana fapple drapple

exec_test $N 20 "$(echo apple*) " 'apple*'
exec_test $N 21 "$(echo *apple) " '*apple'


rm apple apple1 apple2 apple3 applebananna bannana fapple drapple
