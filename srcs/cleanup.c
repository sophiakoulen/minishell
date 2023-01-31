/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 12:04:24 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_cleanup(t_list *pipeline)
{
	ft_lstclear(&pipeline, (void (*)(void *))item_list_cleanup);
}
