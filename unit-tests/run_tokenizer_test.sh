#!/bin/zsh
# Tokenizer unit test

source unit_test_framework.sh

make tokenizer
echo "\n${ITALIC}${YELLOW}Testing the tokenizer${RESET}"

# these tests where written by me, they are not infallable

exec_test 0 '&&||< >>>| some_test && more  ||  make test_tokenizer' '&& || < { } >> > | { some_test } && { more  } || {  make test_tokenizer} end'
exec_test 1 'diff <(echo "$2") <(echo "$RES")' '{diff } < ( {echo "$2"} ) { } < ( {echo "$RES"} ) end'
exec_test 2 'this <<<<<<<<<(()()()()()())))))))&& is stupid' '{this } << << << << < ( ( ) ( ) ( ) ( ) ( ) ( ) ) ) ) ) ) ) ) && { is stupid} end'
# to implement
exec_test 3 'testing double quotes detection"&&" ||hello' '{testing double quotes detection"&&" } || {hello} end'
exec_test 4 "and single quote detection '||' <<<hello" '{and single quote detection "||" } << < {hello} end'

# TODO: what should the token bihaviour be if input is empty string? An end token or nothing
exec_test 5 '' 'type end'
exec_test 6 'testing ending with newline


' '{testing ending with newline} end'
exec_test 7 '<' '< end'
exec_test 8 ' ' '{ } end'
exec_test 9 '|<|<<' '| < | << end'
exec_test 10 '(<(|()|)>)' '( < ( | ( ) | ) > ) end'
exec_test 11 'or || pipe | heredoc << in < out_append >> out > open ( close ) and && end
' '{or } || { pipe } | { heredoc } << { in } < { out_append } >> { out } > { open } ( { close } ) { and } && { end} end'
