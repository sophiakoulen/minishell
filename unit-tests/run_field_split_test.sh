#!/bin/zsh
# field split unit test

source unit_test_framework.sh

N=field_split

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

exec_test $N 0 '{no_split}' "no_split"
exec_test $N 1 '{this} {should} {be} {split}' "this should be split"
exec_test $N 2 '{this} {should} {be} {split}' "this	should	be	split"
exec_test $N 3 '{this"should"} {be} {split}' "this\"should\" be split"
exec_test $N 4 '{this" should"} {be} {split}' "this\" should\" be split"
exec_test $N 5 '{"this "} {be"  "split}' '"this " be"  "split'
exec_test $N 6 "{'that '} {this} {' what'}" "'that ' this ' what'"
