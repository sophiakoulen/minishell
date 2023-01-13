#!/bin/zsh
# Tokenizer unit test

RESET="\033[0m"
GERY="\033[90m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
BLUE="\033[34m"
MAGENTA="\033[35m"
YELLOW="\033[33m"

BOLD="\033[1m"
ITALIC="\033[3m"

function exec_test()
{
	local RES=$(./tokenizer.test $2)
	# local DIFF_RES=$(diff <(echo "$2") <(echo "$RES"))
	# cat -e <(echo $DIFF_RES)
	if [[ $RES == $3 ]]; then
		printf "${BLUE}%2s ${BOLD}${GREEN}OK${RESET}\n" "$1"
	else
		printf "${BLUE}%2s ${BOLD}${RED}KO${RESET}\n" "$1"
		echo "   ${BOLD}${RED}:${RESET}  Expected '$3'"
		echo "   ${BOLD}${RED}:${RESET}  Received '$RES'"
	fi
}


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
