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
	local RES=$(./$1.test $3)
	# local DIFF_RES=$(diff <(echo "$2") <(echo "$RES"))
	# cat -e <(echo $DIFF_RES)
	if [[ $RES == $4 ]]; then
		printf "${BLUE}%2s ${BOLD}${GREEN}OK${RESET}\n" "$2"
	else
		printf "${BLUE}%2s ${BOLD}${RED}KO${RESET}\n" "$2"
		echo "   ${BOLD}${RED}:${RESET}  Expected '$4'"
		echo "   ${BOLD}${RED}:${RESET}  Received '$RES'"
	fi
}
