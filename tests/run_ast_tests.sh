#!/bin/zsh

#testing the ast

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing the AST ${RESET}"

echo "\n\t${ITALIC}${MAGENTA}&& flow control${RESET}"

exec_stdout 0 \
'
true && true && true && false && true
echo $?
true && true && true && true && false
echo $?
true && false && true && true && true true && true && true && true && true && true && true && true && true && true && true && true && true && true
echo $?
false && false && true
echo $?
'
exec_stdout 1 \
'
echo this && false && echo that
echo $?
echo yes && echo yesss && false && echo not
echo $?
echo yes && echo yesss && false && echo not
echo $?
false && echo a && echo b && echo c
echo $?
'
exec_stdout 2 \
'
echo this && that && echo bbbb
echo $?
echo here && true && echo there
echo $?
pwd && export a="this" | echo $a && echo $a
echo $?
'
# issue
exec_stdout 3 \
'
cd && echo r*h
'
exec_stdout 4 \
'
echo -n $USER | cat -e | cat -e && echo $SHLVL | false && false
cd .. && pwd && cd .. && pwd && echo *
# cd .. && pwd && cd .. && echo * && ls -la
'

echo "\n\t${ITALIC}${MAGENTA}|| flow control${RESET}"


exec_stdout 5 \
'
false || true || false || false || true
echo $?
true || false || true || false || false || true
echo $?
true || true || true || true || true || true || true || true || true || true || true || true || true || false
echo $?
'
exec_stdout 6 \
'
false || true || false || false || echo -n hello 42
echo $?
true || false || true || false || false || true || echo here
echo $?
true || true || true || echo a || true || echo b || false || echo c
echo $?
echo 42 || echo 4 || echo life || false || true
echo $?
true || true || false || echo not || true
echo $?
'
exec_stdout 7 \
'
cd .. || false || echo *
echo $?
ls || git status || true
echo $?
false || pwd || touch test || cat test || ls || false
echo $?
rm test || git status || echo no status || false
echo $?
cd tests || echo *.sh || touch __here___ || sleep 10 || rm __here___
cd tests
touch __42__
echo $?
echo *_*
rm __42__
echo $?
'
echo "\n\t${ITALIC}${MAGENTA} && and || flow control${RESET}"

exec_stdout 8 \
'
true || false && true
echo $?
false || true || true && true || false && true || echo done && false
echo $?
true && true || false && true || false || true
echo $?
echo a && echo b || echo c || echo d && echo e || echo f && echo g || false
echo $?
'

exec_stdout 9 \
'
printf "this is here\n" && sleep 1 || echo no | false
echo $?
echo yes | false | false && printf "stop
echo to do more tests
'
