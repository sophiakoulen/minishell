#!/bin/zsh
# Tokenizer unit test

RESET="\033[0m"
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
	local RES=$(./test_tokenizer $2)
	# local DIFF_RES=$(diff <(echo "$2") <(echo "$RES"))
	# cat -e <(echo $DIFF_RES)
	if [[ $RES == $3 ]]; then
		echo "${BLUE}$1 ${BOLD}${GREEN}OK${RESET}"
	else
		echo "${BLUE}$1 ${BOLD}${RED}KO${RESET}"
		echo "  ${BOLD}${RED}:${RESET}  Expected : '$3'"
		echo "  ${BOLD}${RED}:${RESET}  Received : '$RES'"
	fi
}


make test_tokenizer
echo "\n${ITALIC}${YELLOW}Testing the tokenizer${RESET}"

# these tests where written by me, they are not infallable

exec_test 0 '&&||< >>>| some_test && more  ||  make test_tokenizer' 'type && type || type < str   type >> type > type | str  some_test  type && str  more   type || str   make test_tokenizer type end'
exec_test 1 'diff <(echo "$2") <(echo "$RES")' 'str diff  type < type ( str echo "$2" type ) str   type < type ( str echo "$RES" type ) type end'
exec_test 2 'this <<<<<<<<<(()()()()()())))))))&& is stupid' 'str this  type << type << type << type << type < type ( type ( type ) type ( type ) type ( type ) type ( type ) type ( type ) type ( type ) type ) type ) type ) type ) type ) type ) type ) type && str  is stupid type end'
exec_test 3 'testing double quotes detection"&&"||hello' 'str testing double quotes detection"&&" type || str hello type end'
exec_test 4 "and single quote detection '||' <<<hello" "str and single quote detection '||'  type << type < str hello type end"

# TODO: what should the token bihaviour be if input is empty string? An end token or nothing
exec_test 5 '' 'type end'
exec_test 6 '


' 'type end'
exec_test 7 '<' 'type < type end'
exec_test 8 ' ' 'str   type end'
