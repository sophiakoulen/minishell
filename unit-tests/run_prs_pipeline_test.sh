#!/bin/zsh
# parse_cmd unit test

source unit_test_framework.sh

N=prs_pipeline

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# Normal use cases tests 

exec_test $N 0 "1
[][<< EOF]" "<<EOF"

exec_test $N 1 "1
[][<< EOF > in > in < out << OUT << out]" "<<EOF >in  >in <out <<OUT <<   out"

exec_test $N 2 "1
[hello world this a test][]" "hello world this a test"

exec_test $N 3 "1
[hello world this a test][]" "   	hello	world this a test"

exec_test $N 4 "1
[hello world this a test][< in > out < in2 << in3 << in4 < in5 >> hey]" "  <in>out<in2<<in3<< in4 	hello	<in5 world this a test>>hey"

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

exec_test $N 10 "0" ""

exec_test $N 11 "0" "    "

#Error cases

