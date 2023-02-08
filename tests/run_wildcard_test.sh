#!/bin/zsh

#function testing for minishell

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing wildcard expansion ${RESET}"

touch	Afirst Zfirst Zafirstest apple apple1 apple2 apple3 papplez applebananna bannana \
		fapple drapple .hidden .hid.this not.hidden ..what aaaazzzzaaazz thisthatthis \
		simplified.c srcs

exec_test 0 \
'
ls
echo *
'
exec_test 1 \
'
ls
echo *.sh
'
exec_test 2 \
'
ls
echo
'
#issue #110
exec_test 3 \
'
echo s*s*
'

rm	Afirst Zfirst Zafirstest apple apple1 apple2 apple3 papplez applebananna bannana \
		fapple drapple .hidden .hid.this not.hidden ..what aaaazzzzaaazz thisthatthis
