# MINISHELL

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
