#!/bin/zsh
# Tokenizer unit test

source unit_test_framework.sh

make parsing
echo "\n${ITALIC}${YELLOW}Testing the parser${RESET}"

# these tests where written by me, they are not infallable

exec_test 0 'echo hello | cat -e | new_test' '{echo hello } | {{ cat -e } | { new_test}}'


./parsing.test 'echo hello | cat -e | new_test'


# exec_test 0 'echo hello | cat -e' '{echo hello  |  cat -e}'
