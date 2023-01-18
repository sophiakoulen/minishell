/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:28:02 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 13:06:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	exec_pwd(argv);
	return (0);
}
