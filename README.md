# MINISHELL

some readme


## Extracts from POSIX

    # - If the token is an operator, the token identifier for that operator shall result.
    # - If the string consists solely of digits and the delimiter character is one of '<' or '>', the token identifier IO_NUMBER shall be returned.
    # - Otherwise, the token identifier TOKEN results.
	# source : https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10

    # The WORD tokens shall have the word expansion rules applied to them immediately before the associated command is executed, not at the time the command is parsed.
	# what the heck! source : same as above ^
## Grammar

<program> ::= <comand_list> <end>
            | <end>

<comand_list> ::= <comand_list> <and_or>

<and_or> ::= <pipeline>
           | <and_or> '&&' <pipeline>
           | <and_or> '||' <pipeline>

<pipeline> ::= <command>
             | <pipeline> '|' <command>



<end> ::= '\n' | '\r\n' | '\0'

<line> ::= <cmd> <end>

<cmd> ::= <tiem>
        | <cmd> <tiem>

<redirection> ::=  '>' <word>
                |  '<' <word>
                |  <number> '>' <word>
                |  <number> '<' <word>
                |  '>>' <word>
                |  <number> '>>' <word>
                |  '<<' <word>
                |  <number> '<<' <word>

line := cmd { `|` cmd } NEWLINE;

cmd := item { item } ;

item := [ `<<` | `<` | `>>` | `>` ] STRING ;
