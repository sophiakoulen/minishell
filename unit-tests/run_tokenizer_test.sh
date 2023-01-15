#!/bin/zsh
# Tokenizer unit test

source unit_test_framework.sh

N=tokenizer

make $N
echo "\n${ITALIC}${YELLOW}Testing the $N${RESET}"

# these tests where written by me, they are not infallable
# exec_test <test exicutable> <test number> <expected result> <arg1> <arg2> <..>

exec_test $N 0 '&& || < >> > | {some_test} && {more} || {make} {test_tokenizer} end' '&&||< >>>| some_test && more  ||  make test_tokenizer'
exec_test $N 1 '{diff} < ( {echo} {"$2"} ) < ( {echo} {"$RES"} ) end' 'diff <(echo "$2") <(echo "$RES")'
exec_test $N 2 '{this} << << << << < ( ( ) ( ) ( ) ( ) ( ) ( ) ) ) ) ) ) ) ) && {is} {stupid} end' 'this <<<<<<<<<(()()()()()())))))))&& is stupid'
# to implement
exec_test $N 3 '{testing} {double} {quotes} {detection"&&"} || {hello} end' 'testing double quotes detection"&&" ||hello'
exec_test $N 4 "{and} {single} {quote} {detection} {'||'} << < {hello} end" "and single quote detection '||' <<<hello"
# exec_test $N 5 "" 'end' #this case can't be tested with shell the empty quote is not given as an argument
exec_test $N 6  '{testing} {ending} {with} {newline} end' 'testing ending with newline


'
exec_test $N 7 '< end' '<'
exec_test $N 8 'end' ' '
exec_test $N 9 'end' ' 		  	  '
exec_test $N 10 '| < | << end' '|<|<<'
exec_test $N 11 '( < ( | ( ) | ) > ) end' '(<(|()|)>)'
exec_test $N 12 '{or} || {pipe} | {heredoc} << {in} < {out_append} >> {out} > {open} ( {close} ) {and} && {end} end' 'or || pipe | heredoc << in < out_append >> out > open ( close ) and && end
'
exec_test $N 13 '{string} | | {string} end' '  string    |   |    string   '
exec_test $N 14 '{string} || {string} end' 'string||string'
exec_test $N 15 '{string} || {string} end' 'string || string'
exec_test $N 16 '{string} | | {string} end' ' string | |string'
exec_test $N 17 '{quote} {"&&"} end' 'quote "&&"'
exec_test $N 18 "{quote} {'| | |'} end" "quote '| | |'"
exec_test $N 19 "{'hello'} {'|'} {'world'} end" "'hello' '|' 'world'"
exec_test $N 20 "{'good'} && {'bye'} end" "'good' && 'bye'"
exec_test $N 21 '{"greetings"} {"|"} {"earth"} end' '"greetings" "|" "earth"'
exec_test $N 22 '{"good"} && {"bye"} end' '"good" && "bye"'
