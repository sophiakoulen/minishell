#!/bin/zsh

source test_framework.sh

echo "${BOLD}${YELLOW}
-----------------------
 Running general tests
-----------------------
${RESET}\n"

find . -name "run*.sh" -print | zsh
