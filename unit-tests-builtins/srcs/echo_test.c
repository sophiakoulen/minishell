/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:04:35 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 15:09:38 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	if(argc == 1)
		return(0);
	// exec_builtin(e_echo, argv + 1)
	// exec_echo(argv + 1);
	return (exec_builtin(e_echo, argv + 1));
}
