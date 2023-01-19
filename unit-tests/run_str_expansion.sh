#!/bin/zsh
# String expansion unit test

source unit_test_framework.sh

N=str_expansion

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


exec_test $N 99 '{$USR} {-la}' '$USR -la'
