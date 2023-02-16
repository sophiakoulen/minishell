#!/bin/zsh
# Tokenizer unit test

source ../tests-unit/unit_test_framework.sh

N=pwd

make $N
echo "\n${ITALIC}${YELLOW}Testing $N builtin${RESET}"

# these tests where written by me, they are not infallable
EXE_PATH=$(pwd | cut -c 2-)
EXE_PATH+="/"

exec_test $N 0 $(pwd) ''
