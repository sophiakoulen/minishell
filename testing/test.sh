#/bin/bash

MINI=../minishell

echo testing minishell...

#printf "echo hello" | $MINI >actual

#printf "echo hello" | bash >expected

$MINI >actual <<EOF
echo hello
EOF

bash >expected <<EOF
echo hello
EOF