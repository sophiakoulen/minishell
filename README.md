# Minishell

As part of the 42Lausanne curriculum, we have to build a simplified shell,
imitating the behaviour of bash. We need to handle pipelines, redirections
and variable expansion.

## Getting started

To test our project, clone this repository. This repository contains submodules,
so you'll have to fetch them as well:
```bash
git clone https://github.com/sophiakoulen/minishell.git
git submodule update --init --recursive
```

This project depends on the readline library.
You can download it on linux using
```bash
sudo apt install lib32readline8 lib32readline-dev libreadline8 libreadline-dev
```
If you're on MacOs, you can install readline using the homebrew package manager.
If you're at 42, use this: [42homebrew](https://github.com/kube/42homebrew).
```bash
brew install readline
```

If for any reason you cannot install readline in the compiler's default directory,
you can add the path to readline in a READLINE environment variable and our
Makefile will use it.
Eg:
```bash
# or ~/.bashrc depending on the shell you're using
vim ~/.zshrc
# add line
export READLINE=/Users/znichola/.brew/Cellar/readline/8.2.1
```

Now it's time to compile our minishell and run it:
```bash
cd minishell
make
./minishell
```

Have fun breaking our Minishell!

## What is a mini shell, exactly?

Let's give some explanation about what a unix shell is and what it does.
Why is it called shell? Because it's a shell around the operating system
and it's functionalities.
The purpose of the shell is to give the user access to the computer's great
capacity to accomplish all sorts of things. By 'things' we mean 'programs'.
The shell itself is a program. It's a program that allows the user to run and
manage other programs.

### The interactive shell

An interactive shell like bash, displays a prompt, waiting for user's input.
The input is supposed to be a command and the output will be the result of the
command or an error message if something went wrong.

```
minishell$ echo "hello world"
hello world
minishell$ printf "printing some text into a file" >outfile.txt
minishell$ nonexisting command with arguments
minishell: nonexisting: command not found
minishell$ export var=123
minishell$ export foo!=bar
minishell: export: `foo!': not a valid identifier
minishell$
```

### Executing commands

The basic purpose of a shell is to allow us to execute commands.
When trying a simple command, the first word is the name of the program,
the following words are arguments for the program.

The thing the shell now needs to know is: does this command exist and if so,
where is this program located?

There are 2 possibilities:
- The user has entered an absolute path, with slashes, like `/bin/ls` or
`./minishell`. Then we just need to check if that filename is executable.
- The user has entered just a command name without any slashes, like `echo` or
`valgrind` or `clear`. Then, we need to check if the command is a builtin,
meaning, the shell itself knows how to execute the command. Examples of such
builtins are `cd`, `pwd`, `echo`, `export`, `unset`, `env`, `exit`. If it
isn't, the shell will look in all the directories of the PATH variable until
it finds an executable program with that name.

### Pipelines

The `|` pipe operator allows to send to output of a command to the input of another command.
Note that the two commands are launched concurrently, meaning that we do not wait for the first
command to finish before launching the second.

Example 1: `cat "file.txt" | grep hello` will send the contents of "file.txt" to the grep command which will filter the text and print all lines containing the word "hello".

Example 2: `sleep 10 | echo test` will print "test" immediately, since both commands are launched at the same time.

Example 3: `cat "file.txt" | grep hello | grep world` will filter the text and print only lines containing both "hello" and "world".

### Input and output file redirections

Like bash, we can tell a command to take input or output from a file.

#### `>` writes output to a file
Example 1: `echo hello >outfile.txt` will print "hello" in outfile.txt.

#### `>>` writes output to file, in append mode
That means, the output will be add to the enf of the file's existing contents.

#### `<` take input from a file
Example 2: `grep hello <infile.txt` will print all lines from infile.txt containing the string "hello" and print it on the terminal.

#### `<<` takes input from a here-document
This means, the input will be taken from the standard input until a delimiter is reached.

Example 3: `cat <<THIS_IS_THE_END` will take input from stdandard output end send it to the "cat" program, until the string "THIS_IS_THE_END" is found, on its own line.
Note that the shell waits to have received the whole here-doc input before sending it to the "cat" program.

Note that file redirections have priority over pipe redirections.

Example 4: `echo "hello world" >outfile.txt | cat` will not send any input to the "cat" program, since echo's input is redirected to the "outfile.txt" file.

### Environment variables

As part of the assignments, we have to handle environment variables and
variable substitution.

This means we need to be able to modify the environment using the `export` and
`unset` commands.
We also need to be able to subtitute variable names for by their values if
preceded by a dollar sign.
This also means handling single and double quotes, which can be quite tricky.

### Why it's a mini shell and not a shell

Bash is a sophistacted software with tens of thousands of lines of code.
It has not the features we mentioned above and much more.
Bash can:
- redirect not only standard output put also standard error output
- have job control (the user can decide to pause and continue certain tasks)
- have multiline input
- understand simple mathematical expressions
- many more features
And more importantly, Bash can handle control structures: conditions like the
`if`-statement and the `for`-loop. That makes Bash, unlike our Minishell, a
real programming language.

## How we built our Minishell

Let's give some explanation about how we solved this assignment.
First, we did a little research about Bash and the different components
of a simple shell.
One of the articles that was most helpful can be found here:
[The Bourne-Again Shell - Chet Ramey](http://aosabook.org/en/bash.html).
It is written by Bash's current maintainer.

We quickly identified two main components of the Minishell: parsing and execution.
Parsing is the act of generating a structure from raw data.
Execution is the act of performing the task represented by that structure.

Here are some slightly more detailed steps:
1. Reading input
2. Dividing the input into tokens
3. Parsing these tokens into a semi-definitive structure
4. Processing this semi-definitive structure into a definitive structure
5. Executing the pipeline associated to that structure
6. Computing the result of that pipeline

## Grammar

```ebnf
<commandline> ::= <conditionnal>
				| <conditionnal> "&&" <conditionnal>
				| <conditionnal> "||" <conditionnal>

<conditionnal> ::= <pipeline>
				| "(" <commandline> ")"

<pipeline> ::=  <command>
             |  <pipeline> "|" <command>

<command>  ::=  <item>
			 | <command> <item>

<item>  ::= WORD
		| <redir> WORD

<redir>  ::=  "<"  |  ">"  |  ">>" | "<<"
```
