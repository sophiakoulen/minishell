/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:27:09 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/01 11:53:00 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Need to free only the contents of cmd,
	not cmd itself!
*/
void	cmd_cleanup(t_cmd *cmd)
{
	free(cmd->full_path);
	free(cmd->hd_buffer);
	strarr_cleanup(cmd->args);
}
