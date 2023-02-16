#!/bin/zsh
# String expansion unit test

source unit_test_framework.sh

N=quote_removal

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

exec_test $N 0 '{single}' "'single'"
exec_test $N 1 '{single with space}' "'single with space'"
exec_test $N 2 '{  single  }' "'  single  '"
exec_test $N 3 '{    abc    efg   }' "'    abc    efg   '"
exec_test $N 4 '{ " this  "  }' "' \" this  \"  '"
exec_test $N 5 '{twothings}' "'two''things'"
exec_test $N 6 '{twothingsthree}' "'two''things''three'"
exec_test $N 7 '{a}' "'a'"
exec_test $N 8 '{}' "''"
exec_test $N 9 '{foobar}' "foo'bar'"
exec_test $N 10 '{foobar}' "foo''bar"
exec_test $N 11 '{emptystr}' "emptystr''"
exec_test $N 12 '{hello_istuck }' "'hello'_istuck' '"
exec_test $N 13 '{incomplete}' "incomplete'"
exec_test $N 14 '{start}' "'start"
exec_test $N 15 '{start}' "'start"

# double quotes
exec_test $N 16 '{qq}' '"qq"'
exec_test $N 17 '{}' '""'
exec_test $N 18 '{qqbb}' 'qq"bb"'
exec_test $N 19 '{bbqq}' '"bb"qq'
exec_test $N 20 '{}' '""""'

# mix
exec_test $N 21 '{ssqq}' "'ss'\"qq\""
exec_test $N 22 '{}' "''\"\""
exec_test $N 23 '{bb}' "\"bb\"''"
exec_test $N 24 '{asd}' "''\"asd\""
exec_test $N 25 '{thisasd}' "this\"asd\""
exec_test $N 26 '{  " inside  "  }' "'  \" inside  \"  '"
exec_test $N 27 "{  ' inside '  q}" "\"  ' inside '  q\""

# backslashes

exec_test $N 28 "{hello\world}" "hello\world"
exec_test $N 29 "{hey\'}" "\"hey\'\""
exec_test $N 30 '{b"b}' "\"b\\\"b\""
exec_test $N 31 '{asd\\\}' "asd\\\\\\\\\\\\"
exec_test $N 32 "{'hello'}" "\'hello\'"
exec_test $N 33 '{  " inside  "  }' '  \" inside  \"  '


# # variable expansion in double quotes
# exec_test $N 28 "{$LOGNAME}" '"$LOGNAME"'
# exec_test $N 29 "{$PATH}" '"$PATH"'
# exec_test $N 30 "{what$SHLVL}" '"what$SHLVL"'
# exec_test $N 30 "{this'$SHLVL'}" "\"this'$SHLVL'\""
# exec_test $N 31 "{$USER$SHELL}" '"$USER$SHELL"'


# exec_test $N 99 '{$USR} {-la}' '$USR -la'
