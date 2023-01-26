#!/bin/zsh
# parse_cmd unit test

source unit_test_framework.sh

N=parsing

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# Zero command but redirections
echo "\nTesting zero command with redirections:"

exec_test $N 0 "1
[][<< EOF]" "<<EOF"

exec_test $N 1 "1
[][<< EOF > in > in < out << OUT << out]" "<<EOF >in  >in <out <<OUT <<   out"

echo "\nTesting one command no redirections:"

exec_test $N 2 "1
[hello world this a test][]" "hello world this a test"

exec_test $N 3 "1
[hello world this a test][]" "   	hello	world this a test"

echo "\nTesting one command multiple redirections:"

exec_test $N 4 "1
[hello world this a test][< in > out < in2 << in3 << in4 < in5 >> hey]" "  <in>out<in2<<in3<< in4 	hello	<in5 world this a test>>hey"

echo "\nTesting mutiple commands:"

exec_test $N 5 "2
[hello][]
[grep test][]" "hello | grep test"

exec_test $N 6 "2
[][<< EOF]
[test test test][> 'infile infile']" "<<EOF|   test test >'infile infile' test"

exec_test $N 7 "3
[echo][<< hello]
[hey][< in > out]
[test][]" "echo <<hello    |<in>out hey|test"

exec_test $N 8 "1
[echo '|' '| ' hey'|'test][<< hello < in > out]" "echo <<hello   '|' '| ' <in>out hey'|'test"

exec_test $N 9 "1
[\"this is a command|\" 'arg1 ' \"arg2\"][]" "\"this is a command|\" 'arg1 ' \"arg2\""

# empty lines
echo "\nTesting empty lines:"

exec_test $N 10 "" ""

exec_test $N 11 "" "    "

exec_test $N 12 "" "
"

# syntax errors
echo "\nTesting syntax errors:"

exec_test $N 13 "" "echo |"

exec_test $N 14 "" "|"

exec_test $N 15 "" "||"

exec_test $N 16 "" "&|>"
