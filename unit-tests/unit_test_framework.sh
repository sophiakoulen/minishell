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
	FUNC=$1
	NUM=$2
	EXPCTED=$3
	shift	# moved past the function
	shift	# moved past the number
	shift	# moved past the expected
	local RES=$(./$FUNC.test $@)
	if [[ $RES == $EXPCTED ]]; then
		printf "${BLUE}%2s ${BOLD}${GREEN}OK${RESET}\n" "$NUM"
	else
		printf "${BLUE}%2s ${BOLD}${RED}KO${RESET}\n" "$NUM"
		echo "   ${BOLD}${RED}:${RESET}  Inputted '$@'"
		echo "   ${BOLD}${RED}:${RESET}  Expected '$EXPCTED'"
		echo "   ${BOLD}${RED}:${RESET}  Received '$RES'"
	fi
}
