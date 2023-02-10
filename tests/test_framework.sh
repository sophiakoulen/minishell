#!/bin/zsh

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

MINI=../minishell

function exec_stdout()
{
	NUM=$1
	ARG=$2

	>tmp printf $ARG
	RES="$($MINI <tmp 2>/dev/null)"
	EXPCTED="$(bash <tmp 2>/dev/null)"

	if [[ $RES == $EXPCTED ]]; then
		printf "${BLUE}%2s ${BOLD}${GREEN}OK${RESET}\n" "$NUM"
	else
		printf "${BLUE}%2s ${BOLD}${RED}KO${RESET}\n" "$NUM"
		echo "   ${BOLD}${RED}:${RESET}  Inputted '$ARG'"
		echo "   ${BOLD}${RED}:${RESET}  Expected '$EXPCTED'"
		echo "   ${BOLD}${RED}:${RESET}  Received '$RES'"
	fi

	rm tmp
}

function exec_stderr()
{
	NUM=$1
	ARG=$2

	>tmp printf $ARG
	RES="$($MINI <tmp 2>&1)"
	EXPCTED="$(bash <tmp 2>&1)"

	#RES=${RES%exit} # we remove the last exit as minishell is polite and like to print it, but bash does not!

	if [[ $RES == $EXPCTED ]]; then
		printf "${BLUE}%2s ${BOLD}${GREEN}OK${RESET}\n" "$NUM"
	else
		printf "${BLUE}%2s ${BOLD}${RED}KO${RESET}\n" "$NUM"
		echo "   ${BOLD}${RED}:${RESET}  Inputted '$ARG'"
		echo "   ${BOLD}${RED}:${RESET}  Expected '$EXPCTED'"
		echo "   ${BOLD}${RED}:${RESET}  Received '$RES'"
	fi

	rm tmp
}

# t1=\
# '
# export var="a b c"
# echo $var
# lsasda
# '

# exec_stdout 1 \
# '
# export var="a b c"
# echo $var
# lsasda
# '
