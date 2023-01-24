#!/bin/zsh
# String expansion unit test

source unit_test_framework.sh

N=param_expansion

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

exec_test $N 0 "{$USER}" '$USER'
exec_test $N 1 "{this_$USER}" 'this_$USER'
exec_test $N 2 "{$USERZZZZ}" '$USERZZZZ'
exec_test $N 3 "{'qqqqq'}" "'qqqqq'"
exec_test $N 4 "{\"qqqqq\"}" '"qqqqq"'
exec_test $N 5 "{$USER\"quote\"}" '$USER"quote"'
exec_test $N 6 "{\"this ' that  ' here\"}" "\"this ' that  ' here\""
exec_test $N 7 "{\"''\"}" "\"''\""
exec_test $N 8 "{\"''''''\"}" "\"''''''\""
exec_test $N 9 "{\"'\"}" "\"'\""

# nested $ in eschaped charaters
exec_test $N 10 "{\"$USER\"}" "\"\$USER\""
exec_test $N 11 "{\"! $USER is awsome\"}" "\"! \$USER is awsome\""
exec_test $N 12 "{\"hello $USER $SHELL\"}" "\"hello \$USER \$SHELL\""
exec_test $N 13 "{\"hello $USER $SHELL\"}" "\"hello \$USER \$SHELL\""
exec_test $N 14 "{\"hello \"}" "\"hello \$\$\$\$\""
exec_test $N 15 "{42}" '$?'
exec_test $N 16 "{\"42\"}" '"$?"'
exec_test $N 17 "{\"hello \"}" "\"hello \$\$\$\$\""
