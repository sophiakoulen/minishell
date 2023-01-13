/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:48:15 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/12 14:51:31 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_cmd_internal	*prepare_cmd(t_cmd *cmd, t_exec exec_utils, int index)
{
	t_cmd_internal	*ci;

	ci = malloc(sizeof(*ci));
	//protect
	ci->status = 0;
	ci->ifd = 
	ci->ofd = 
	
}