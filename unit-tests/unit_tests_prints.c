/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests_prints.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:19:21 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 08:22:47 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// work in progress, would need to configure the makefile to use multiple files
// to compile the unit tests, don't want it get annoying managing files

void	print_token_list_minimal(t_token *tok)
{
	if (!tok)
		return ;
	if (tok->type == e_end)
		ft_printf("end");
	else if (tok->type == e_string)
		ft_printf("{%s} ", tok->str);
	else
		ft_printf("%s ", ret_token_literal(tok->type));
	if (tok->next)
		print_token_list_minimal(tok->next);
}
