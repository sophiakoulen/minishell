#!/bin/zsh

# https://www.baeldung.com/linux/source-include-files
source $(dirname "$0")/test_framework.sh

echo "${BOLD}${YELLOW}
------------------------------------
 Running general functionlity tests
------------------------------------
${RESET}\n"

cd $(dirname "$0")
find . -name "run*.sh" -print | zsh
