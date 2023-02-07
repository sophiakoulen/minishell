#!/bin/zsh
# Wildcard Expansion unit test

source unit_test_framework.sh

N=wildcard_exp

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

FILES="apple apple1 apple2 apple3 applebananna bannana fapple drapple .hidden"

touch Afirst Zfirst Zafirstest apple apple1 apple2 apple3 papplez applebananna bannana fapple drapple .hidden .hid.this not.hidden ..what

exec_test $N 0 "$(echo *) " '*'
exec_test $N 1 "$(echo *.sh) " '*.sh'
exec_test $N 2 "$(echo run*) " 'run*'
exec_test $N 3 "$(echo *_*) " '*_*'
exec_test $N 4 "$(echo run*.sh) " 'run*.sh'
exec_test $N 5 "$(echo run*test*sh) " 'run*test*sh'

# make sure there is no file that will match test*
exec_test $N 6 "$(echo test'*') " 'test*'

exec_test $N 7 "$(echo file) " 'file'
exec_test $N 8 "$(echo *file) " '*file'

exec_test $N 9 "$(echo .*) " '.*'
exec_test $N 10 "$(echo *.sh) " '*.sh'
exec_test $N 11 "$(echo *M*) " '*M*'
exec_test $N 12 "$(echo *.*) " '*.*'

exec_test $N 13 "$(echo .**) " '.**'
exec_test $N 14 "$(echo **.sh) " '**.sh'


exec_test $N 15 "$(echo *apple*) " '*apple*'
exec_test $N 16 "$(echo apple*) " 'apple*'
exec_test $N 17 "$(echo *apple) " '*apple'
exec_test $N 18 "$(echo A*) " 'A*'

exec_test $N 18 "$(echo *.sh) " '*".sh"'

rm Afirst Zfirst Zafirstest apple apple1 apple2 apple3 papplez applebananna bannana fapple drapple .hidden .hid.this not.hidden ..what
