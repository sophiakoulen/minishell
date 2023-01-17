#!/bin/zsh
# parse_cmd unit test

source unit_test_framework.sh

N=prs_cmd

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 "PARSED_CMD
~~args~~
 0. echo
 1. test
~~redirs~~
>> hello < in1 > out1 < in2 > out2 > out3>> out4" " >>hello <in1 >out1 <in2 >out2 >out3 >>out4 echo test "

exec_test $N 1 "PARSED_CMD
~~args~~
~~redirs~~
<< END1" "<<END1"

exec_test $N 2 "PARSED_CMD
~~args~~
~~redirs~~
<< END1" "<<END1 |"

exec_test $N 3 "PARSED_CMD
~~args~~
~~redirs~~
<< END1 > out1 > out2 > out3" "<<END1 >out1 >out2 >out3|"

exec_test $N 4 "Syntax error near unexpected token <
PARSED_CMD
(NULL)" "<<<EOF"

exec_test $N 5 "Syntax error near unexpected token <<
PARSED_CMD
(NULL)" "<<<<EOF    |"
