# MINISHELL

> **Note**
> This project is part of the 42Lausanne curriculum.

## Introduction

In this project, we need to build a simplified version of Bash.
We need to handle pipelines, input and output file redirections and variable expansion.


## Getting Started

- First you need to install readline, you can use the version of brew found here: [42homebrew](git@github.com:kube/42homebrew.git).
- `brew install readline` to install readline
- add readline to your enviroment under `READLINE` eg:
-
```bash
vim .zshrc
# add line
export READLINE=/Users/znichola/.brew/Cellar/readline/8.2.1
```

### About pipelines

The `|` pipe operator allows to send to output of a command to the input of another command.
Note that the two commands are launched concurrently, meaning that we do not wait for the first
command to finish before launching the second.

Example 1: `cat "file.txt" | grep hello` will send the contents of "file.txt" to the grep command which will filter the text and print all lines containing the word "hello".

Example 2: `sleep 10 | echo test` will print "test" immediately, since both commands are launched at the same time.

Example 3: `cat "file.txt" | grep hello | grep world` will filter the text and print only lines containing both "hello" and "world".

### About file redirections

Like bash, we can tell a command to take input or output from a file.

`>` will write output to a file.

Example 1: `echo hello >outfile.txt` will print "hello" in outfile.txt.

`>>` will write output to file, in append mode. That means, the output will be appended to the rest of the file's contents.

`<` will take input from a file.

Example 2: `grep hello <infile.txt` will print all lines from infile.txt containing the string "hello" and print it on the terminal.

`<<` is used to take input from a here-document. This means, the input will be taken from the standard input until a delimiter is reached.

Example 3: `cat <<THIS_IS_THE_END` will take input from stdandard output end send it to the "cat" program, until the string "THIS_IS_THE_END" is found, on its own line.
Note that the shell waits to have received the whole here-doc input before sending it to the "cat" program.

Note that file redirections have priority over pipe redirections.

Example 4: `echo "hello world" >outfile.txt | cat` will not send any input to the "cat" program, since echo's input is redirected to the "outfile.txt" file.

## Extracts from POSIX

- If the token is an operator, the token identifier for that operator shall result.
- If the string consists solely of digits and the delimiter character is one of '<' or '>', the token identifier IO_NUMBER shall be returned.
- Otherwise, the token identifier TOKEN results.
[-source](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10)

The WORD tokens shall have the word expansion rules applied to them immediately before the associated command is executed, not at the time the command is parsed.
what the heck!

## Grammar

### Current dev goal

```ebnf
<commandline> ::= <pipeline> <end>
                | <end>

<pipeline> ::=  <string>
             |  <pipeline> "|" <string>

<string> ::= "any combination of characters really"
```

### Current dev goal rewrite

```ebnf
<commandline> ::= {<pipeline>} <end>

<pipeline> ::=  <string> {"|" <string>}

<string> ::= "any combination of characters really"
```

### Final gramar is something like this

```ebnf

<commandline> ::= <conditional> <end>
                | <end>

<conditional> ::=  <pipeline>
                |  <conditional> "&&" <pipeline>
                |  <conditional> "||" <pipeline>

<pipeline> ::=  <command>
             |  <pipeline> "|" <command>

<command>  ::=  <word>
             |  <redirection>
             |  <command> <word>
             |  <command> <redirection>

<redirection>  ::=  <redirectionop> <filename>

<redirectionop>  ::=  "<"  |  ">"  |  ">"

<end> ::= '\n' | '\r\n' | '\0'

```

last updated on `12 01 2023`
