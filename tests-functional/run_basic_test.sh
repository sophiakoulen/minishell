#!/bin/zsh

# mandatory part

source $(dirname "$0")/test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing mandatory part ${RESET}"

# executing a command
echo "\n\t${ITALIC}${MAGENTA}Executing a command${RESET}"

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
echo "\n\t${ITALIC}${MAGENTA}Executing a pipeline${RESET}"

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

# empty commands
echo "\n\t${ITALIC}${MAGENTA}Empty commands${RESET}"

exec_stderr 14 \
'  '

exec_stderr 15 \
'

'

exec_stderr 16 \
'    				        '

# echo
echo "\n\t${ITALIC}${MAGENTA}The echo builtin${RESET}"

exec_stderr 17 \
'
echo hello world
'

exec_stderr 18 \
'
echo -n hello world
'

exec_stderr 19 \
'
echo hello -n -n -n world
'

exec_stderr 20 \
'
echo -a -b -c hello world
'

exec_stderr 21 \
'
echo
'

exec_stderr 22 \
'
echo -n
'

# return values
echo "\n\t${ITALIC}${MAGENTA}Return values${RESET}"

exec_stdout 21 \
'
echo $?
'

exec_stdout 22 \
'
echo hello$?world
'

exec_stdout 23 \
'
cmdnotexist
echo $?
echo $?
touch forbidden
echo $?
chmod -x forbidden
./forbidden
echo $?
echo $?
rm -f forbidden
'

exec_stdout 24 \
'
<existepas cat
echo $?
>existpas cat
echo $?
touch exists
<exists <existepas cat
echo $?
<existepas <exists <existepas cat
echo $?
rm -f exists existpas
'
rm -f existpas

exec_stdout 25 \
'
touch exists
>>exists >existepas >>existepas >exists
echo $?
rm -f exists existepas
'

exec_stdout 26 \
'
||||||||<<<<>>>>>>>>ywgsywgy wygywgsywgsygwysg
echo $?
'

exec_stdout 27 \
'
export var="a b c"
<$var
echo $?
'

exec_stdout 28 \
'
export var=""
<$var
echo $?
'

exec_stdout 29 \
'
$? +$?+ $? + $?
'

# Double quotes
echo "\n\t${ITALIC}${MAGENTA}Double quotes${RESET}"

exec_stdout 30 \
'"/bin/ls"
'

exec_stdout 31 \
'"/bin/ls" "-la"
'

exec_stdout 32 \
'"/bin/ls -la"
'

exec_stdout 33 \
'echo "cat lol.c | cat > lol.c"
'

exec_stdout 34 \
'"""""""""hello"
""""ls
'

exec_stdout 35 \
"
\"''\\\"\\\"\"
"

# single quotes
echo "\n\t${ITALIC}${MAGENTA}Single quotes${RESET}"

exec_stdout 36 \
"
''
"

exec_stdout 37 \
"
'ls -la'
"

exec_stdout 38 \
"
'ls' '-la' ''
"

exec_stdout 39 \
"
'\$\$\$\$\$\$\$\$'
"

exec_stdout 40 \
"
'\$USER'
"

exec_stdout 41 \
"
'*' '|||||||<<<>>>>>' '\$'
"

exec_stdout 42 \
"
echo '\'
"

# env, export and unset
echo "\n\t${ITALIC}${MAGENTA}Env export and unset${RESET}"

export var="hello"
exec_stdout 43 \
'
env | grep var | sort
'
unset var

exec_stdout 44 \
'
export var="hello"
env | grep var | sort
export var1="world"
export va="test"
echo $var $va $var1
unset $va
echo $va $var $var1
unset $var1
echo $va $var $var1
'

export PWD="abc"
export OLDPWD="defghijk"
exec_stdout 45 \
'
echo $SHLVL
echo $PWD
echo $OLDPWD
'

# cd and pwd
echo "\n\t${ITALIC}${MAGENTA}cd and pwd${RESET}"

exec_stdout 46 \
'
cd ..
/bin/ls
cd tests
/bin/ls
cd .
/bin/ls
cd
/bin/ls
'

exec_stdout 47 \
'
export PWD="AAAAA"
export OLDPWD="BBBBBBBBBB"
cd existepas
/bin/ls
pwd
echo PWD: $PWD
echo OLDPWD: $OLDPWD
cd hello
echo OLDPWD: $OLDPWD
cd
pwd
echo OLDPWD: $OLDPWD PWD: $PWD
'

exec_stdout 48 \
'
export PWD="AAAA"
export OLDPWD="BBBB"
pwd with arguments
pwd
pwd
echo $OLDPWD
'

exec_stderr 49 \
'
pwd .
pwd ..
'

# command finding
echo "\n\t${ITALIC}${MAGENTA}command finding${RESET}"

exec_stdout 50 \
'
unset PATH
ls
'

exec_stderr 51 \
"mkdir dir1 dir2 dir3
touch dir1/prog dir2/prog dir3/prog

echo '#!/bin/bash' >> dir1/prog
echo >> dir1/prog
echo 'echo hello from dir1' >> dir1/prog
chmod +x dir1/prog

echo '#!/bin/bash' >> dir2/prog
echo >> dir2/prog
echo 'echo hello from dir2' >> dir2/prog
chmod +x dir2/prog

echo '#!/bin/bash' >> dir3/prog
echo >> dir3/prog
echo 'echo hello from dir3' >> dir3/prog
chmod +x dir3/prog

export PATH=\$PATH:dir2:dir3:dir1
prog
rm -rf dir1 dir2 dir3
"

exec_stderr 52 \
"mkdir dir1 dir2 dir3
touch dir1/prog dir2/prog dir3/prog

echo '#!/bin/bash' >> dir1/prog
echo >> dir1/prog
echo 'echo hello from dir1' >> dir1/prog
chmod +x dir1/prog

echo '#!/bin/bash' >> dir2/prog
echo >> dir2/prog
echo 'echo hello from dir2' >> dir2/prog
chmod -x dir2/prog

echo '#!/bin/bash' >> dir3/prog
echo >> dir3/prog
echo 'echo hello from dir3' >> dir3/prog
chmod +x dir3/prog

export PATH=\$PATH:dir2:dir3:dir1
prog
rm -rf dir1 dir2 dir3
"

exec_stderr 53 \
"
mkdir dir
touch script.sh
echo '#!/bin/bash' >> script.sh
echo >> script.sh
echo 'echo hello' >> script.sh
chmod +x script.sh
cd dir
../script.sh
./../script.sh
./../dir/../dir/../script.sh
cd ..
rm -rf dir
rm -f script.sh
"

# redirections
echo "\n\t${ITALIC}${MAGENTA}redirections${RESET}"

exec_stderr 54 \
"
<.gitignore cat
cat .gitignore >out
echo hello >>out
echo world >>out
ls -la
rm -f out
"

#empty strings
echo "\n\t${ITALIC}${MAGENTA}empty strings${RESET}"

exec_stdout 55 \
"
''
echo \$?
"

exec_stderr 56 \
"
echo ''
"

exec_stderr 57 \
"
grep ""
"
