/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:40:00 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 12:55:05 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* used in cmd exicution */
#define INFILE 0
#define HEREDOC 1
#define OUTFILE 2
#define APPEND 3

/* Possible token types corresponding strings defined in structs/t_token.c */
# define NUM_TOKEN_LITERALS 9

enum e_token_type
{
	e_or,			// ||
	e_pipe,			// |
	e_heredoc,		// <<
	e_in,			// <
	e_out_append,	// >>
	e_out,			// >
	e_open_brace,	// (
	e_close_brace,	// )
	e_and,			// &&
	e_end,			// \n or \r\n
	e_string,
};


#endif
