# MINISHELL

> **Note**
> This project is part of the 42Lausanne curriculum.

## Introduction

In this project, we need to build a simplified version of Bash.
We need to handle pipelines, input and output redirections and variable expansion.

### About pipelines

The `|` pipe operator allows to send to output of a command to the input of another command.
Note that the two commands are launched concurrently, meaning that we do not wait for the first
command to finish before launching the second.

Example 1: `cat "file.txt" | grep hello` will send the contents of "file.txt" to the grep command which will filter the text and print all lines containing the word "hello".

Example 2: `sleep 10 | echo test` will print "test" immediately, since both commands are launched at the same time.

Example 3: `cat "file.txt" | grep hello | grep world` will filter the text and print only lines containing both "hello" and "world".

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
