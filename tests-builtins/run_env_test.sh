#!/bin/zsh
# Tokenizer unit test

source ../unit-tests/unit_test_framework.sh

N=env

make $N
echo "\n${ITALIC}${YELLOW}Testing $N builtin${RESET}"

# these tests where written by me, they are not infallable

exec_test $N 0 "$(env | grep -v _=/)
_=$(pwd)/bin/env.test" ''

export USER="custom variable"
exec_test $N 1 "$(env | grep -v _=/)
_=$(pwd)/bin/env.test" ''

# "$(env)"

# ./$N.test ''w
