/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:54:08 by znichola          #+#    #+#             */
/*   Updated: 2023/01/11 17:52:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define NUM_TOKEN_LITERALS 9

const char	*tok_strings[NUM_TOKEN_LITERALS] =
{
	"|",
	"<<",
	"<",
	">",
	">>",
	"(",
	")",
	"&&",
	"||",
};

enum e_token_type
{
	e_pipe,			// |
	e_heredoc,		// <<
	e_in,			// <
	e_out,			// >
	e_out_append,	// >>
	e_open_brace,	// (
	e_close_brace,	// )
	e_and,			// &&
	e_or,			// ||
	e_end,			// \n or \r\n
	e_string,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*str;
	struct s_token		*next;
}	t_token;

#endif
