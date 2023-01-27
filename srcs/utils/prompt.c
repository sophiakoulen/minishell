/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:51:06 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/27 15:27:34 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_red(char *prompt)
{
	prompt[18] = '9';

}

void	make_blue(char *prompt)
{
	prompt[18] = '1';
}

void	adjust_color(char *prompt, int retn)
{
	if (retn == 0)
		make_blue(prompt);
	else
		make_red(prompt);
}