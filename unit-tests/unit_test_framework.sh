#!/bin/zsh
# the testing framework for individual tests

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
