#!/bin/zsh
# Tokenizer unit test

source unit_test_framework.sh

N=tokenizer

make $N
echo "\n${ITALIC}${YELLOW}Testing the tokenizer${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 '&&||< >>>| some_test && more  ||  make test_tokenizer' '&& || < >> > | {some_test} && {more} || {make test_tokenizer} end'
exec_test $N 1 'diff <(echo "$2") <(echo "$RES")' '{diff} < ( {echo "$2"} ) < ( {echo "$RES"} ) end'
exec_test $N 2 'this <<<<<<<<<(()()()()()())))))))&& is stupid' '{this} << << << << < ( ( ) ( ) ( ) ( ) ( ) ( ) ) ) ) ) ) ) ) && {is stupid} end'
# to implement
exec_test $N 3 'testing double quotes detection"&&" ||hello' '{testing double quotes detection"&&"} || {hello} end'
exec_test $N 4 "and single quote detection '||' <<<hello" "{and single quote detection '||'} << < {hello} end"
# exec_test $N 5 "" 'end' #this case can't be tested with shell the empty quote is not given as an argument
exec_test $N 6 'testing ending with newline


' '{testing ending with newline} end'
exec_test $N 7 '<' '< end'
exec_test $N 8 ' ' 'end'
exec_test $N 9 ' 		  	  ' 'end'
exec_test $N 10 '|<|<<' '| < | << end'
exec_test $N 11 '(<(|()|)>)' '( < ( | ( ) | ) > ) end'
exec_test $N 12 'or || pipe | heredoc << in < out_append >> out > open ( close ) and && end
' '{or} || {pipe} | {heredoc} << {in} < {out_append} >> {out} > {open} ( {close} ) {and} && {end} end'
exec_test $N 13 '  string    |   |    string   ' '{string} | | {string} end'
exec_test $N 14 'string||string' '{string} || {string} end'
exec_test $N 15 'string || string' '{string} || {string} end'
exec_test $N 16 ' string | |string' '{string} | | {string} end'
exec_test $N 17 'quote "&&"' '{quote "&&"} end'
exec_test $N 18 "quote '| | |'" "{quote '| | |'} end"
exec_test $N 19 "'hello' '|' 'world'" "{'hello' '|' 'world'} end"
exec_test $N 20 "'good' && 'bye'" "{'good'} && {'bye'} end"
exec_test $N 21 '"greetings" "|" "earth"' '{"greetings" "|" "earth"} end'
exec_test $N 22 '"good" && "bye"' '{"good"} && {"bye"} end'
