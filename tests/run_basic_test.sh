#!/bin/zsh

# mandatory part

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing mandatory part ${RESET}"

# executing a command

exec_stdout 0 \
'
/bin/ls
'

exec_stdout 1 \
'
/bin/ls -la
'

exec_stdout 2 \
'
/bin/cat test_framework.sh run_wildcard_test.sh
'

exec_stdout 3 \
'
/bin/cat non-existing non-existing2 non-existing3
'

exec_stdout 4 \
'
touch test1 test2 test3 test4
rm test1 test2 test3 test4
ls
'

exec_stdout 5 \
'
touch forbidden-command
chmod -x forbidden-command
./forbidden-command
rm -rf ./forbidden-command
'

exec_stderr 6 \
"
mkdir new_dir
touch new_dir/cmd.sh
echo '#!/bin/bash' >>new_dir/cmd.sh
echo >>new_dir/cmd.sh
echo 'echo hello world' >>new_dir/cmd.sh
export PATH=\$PATH:./new_dir
chmod +x new_dir/cmd.sh
./new_dir/cmd.sh
rm -rf new_dir
"

exec_stdout 7 \
'
unset PATH
ls
'

exec_stdout 8 \
'
sleep 1
'

# Executing a pipeline

exec_stdout 9 \
'
sleep 1 | sleep 1 | sleep 1
'

exec_stdout 10 \
'
non-existing | printf "helloooo"
'

exec_stdout 11 \
'
cat test_framework.sh | cat -e | cat -e | cat -n | cat -e
'

exec_stdout 12 \
'
huhu|ushuwhsuwhsu|shuwhsuwhsuwushush|hsuwhsuhwu
cat non-existing | echo hello
ls | ls | ls | cat
'

exec_stdout 13 \
'
sleep 1 | cat .gitignore | cat non-existing | hello
cat .gitignore | sleep 1 | touch hello
printf "hey" > hello
./hello | echo hello
chmod +x hello | touch hello2
./hello2
./hello
rm -f hello hello2
'