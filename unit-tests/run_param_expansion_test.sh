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
exec_test $N 10 "{'a''b'}" "'a''b'"
exec_test $N 11 "{'a'l'b'}" "'a'l'b'"

# nested $ in eschaped charaters
exec_test $N 12 "{\"$USER\"}" "\"\$USER\""
exec_test $N 13 "{\"! $USER is awsome\"}" "\"! \$USER is awsome\""
exec_test $N 14 "{\"hello $USER $SHELL\"}" "\"hello \$USER \$SHELL\""
exec_test $N 15 "{\"hello $USER $SHELL\"}" "\"hello \$USER \$SHELL\""
exec_test $N 16 "{\"hello \$\$\$\$\"}" "\"hello \$\$\$\$\""
exec_test $N 17 "{42}" '$?'
exec_test $N 18 "{\"42\"}" '"$?"'
exec_test $N 19 "{\"$USER$HOME$LANG\"}" "\"\$USER\$HOME\$LANG\""
exec_test $N 21 "{$USER'a'$LANG}" "\$USER'a'\$LANG"
exec_test $N 22 "{$USER 'a' $LANG}" "\$USER 'a' \$LANG"
exec_test $N 23 "{$USER \"b\" $LANG}" '$USER "b" $LANG'
exec_test $N 24 "{$USER\"b\"$LANG}" '$USER"b"$LANG'
exec_test $N 25 "{\"$USER\"a'\$LANG'}" "\"\$USER\"a'\$LANG'"

exec_test $N 26 "{\"$USER\"'\$LANG'\" $(expr $SHLVL + 1) \"}" "\"\$USER\"'\$LANG'\" \$SHLVL \""

exec_test $N 27 "{'\$USER'\"$LANG\"}" "'\$USER'\"\$LANG\""
exec_test $N 28 "{'\$USER'abc\"$LANG\"}" "'\$USER'abc\"\$LANG\""
exec_test $N 29 "{\"$USER ' this $LANG\"}" "\"$USER ' this $LANG\""
exec_test $N 30 "{\"$USER''' '$LANG'\"}" "\"$USER''' '$LANG'\""
exec_test $N 31 "{\"$US'ER''' '$LANG'\"}" "\"$US'ER''' '$LANG'\""
# exec_test $N 32 "{\"$USER'a'$LANG\"}" "\"\$USER'a'\$LANG\""
# exec_test $N 33 "{\"$USER'/'$HOME$LANG\"}" "\"\$USER'/'\$HOME\$LANG\""
