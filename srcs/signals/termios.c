/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 06:32:12 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 09:36:55 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	modify the termios setting wich govern the display of ctrl caracters ^C ..
	you can check the current settings with
		stty -a
	look for echoctl we toggle it to -echoctl to
	1 save the termios defaults and set echoctrl to ignored
	0 restor the default termios settings
 */
void	get_set_termios(int toggle)
{
	static struct termios	saved_termios;
	static struct termios	modified_termios;

	if (toggle)
	{
		tcgetattr(STDIN_FILENO, &saved_termios);
		tcgetattr(STDIN_FILENO, &modified_termios);
		modified_termios.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified_termios);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}
