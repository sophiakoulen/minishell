/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:27:09 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 10:29:12 by skoulen          ###   ########.fr       */
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
	free(cmd->hd_delim);
	strarr_cleanup(cmd->args);
}
