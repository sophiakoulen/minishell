/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:34 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 14:20:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>

# include "libft.h"
# include "defines.h"
# include "structs.h"

// # include "tokenizer.h"
// # include "parsing.h"
// # include "execution.h"
// # include "cmd.h"

/* ************************************************************************** */
/*   builtins                                                                 */
/* ************************************************************************** */

int			echo(char **args);
int			pwd(void);

/* ************************************************************************** */
/*   exicution                                                                */
/* ************************************************************************** */

/* heredoc */

void		do_all_heredocs(t_cmd *cmds, int **hd_pipes, int n);

/* find_cmd utils */

char		**extract_path(char **envp);
int			has_slashes(const char *str);
char		*concat_slash(const char *str1, const char *str2);
int			file_ok(char *filename, char **res);

/* find_cmd */

int			find_cmd(char **path, char *filename, char **res);

/* prepare cmd */

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n);
void		cleanup_all_info(t_cmd_info *infos, int n);

/* prepare fds */

t_fds		*prepare_fds(int n);
void		cleanup_fds(t_fds *fds, int n_cmds);

/* exec_utils */

int			compute_return_value(int status);
int			redirect(int input_fd, int output_fd);

/* multiple commands */

int			multiple_commands(t_cmd *cmds, t_fds *fds, int n);

/* ************************************************************************** */
/*   expansion                                                                */
/* ************************************************************************** */

/* var_exp */

char		**variable_expansion(char *str);

/* wild_exp */

char		*wildcard_expansion(char *str);

/* ************************************************************************** */
/*   parsing                                                                  */
/* ************************************************************************** */

/* prs_pipline */


/* prs comandline */

int			parse_commandline(t_tree **tree, t_token *tok);

/* prs pipeline */

int			parse_pipeline(t_tree **tree, t_token **tok);

/* prs command */

int			parse_command(t_tree **tree, t_token **tok);

/* prs item */

// int			parse_item(t_tree **tree, t_token **tok);
int			parse_item(t_redir **redir, t_token **tok);

/* construct cmds */
t_redir		*redir_factory(t_redir *blueprint);
t_cmd		*cmd_factory(t_cmd *blueprint);
int			construct_cmd(t_token **tok, t_cmd **cmd);
int			constuct_cmds(t_token **tok, t_cmd **cmds, int *n_cmds);

/* ************************************************************************** */
/*   tokenizer                                                                */
/* ************************************************************************** */

/* tokenizer */

t_token		*construct_tok_list(char *str);

/* ************************************************************************** */
/*   utils                                                                    */
/* ************************************************************************** */

void		*x_malloc(size_t size, size_t quantity);
int			ft_isspace(int c);

/* tree_ops */

int			get_tree_width(t_tree *tree, int level);
int			get_tree_height(t_tree *tree);
int			get_tree_max_width(t_tree *tree);

/* ************************************************************************** */
/*   structs                                                                  */
/* ************************************************************************** */

/* t_cmd_info.c */

// nothing yet

/* t_cmd.c */

t_cmd		*cmd_factory(t_cmd *blueprint);

/* t_fds.c */

void		close_fds(t_fds *fds, int n);

/* t_redir.c */

t_redir		*redir_factory(t_redir *blueprint);
void		print_redir(t_redir *r);

/* t_token.c */

t_token		*token_factory(t_token *next, char *str, enum e_token_type type);
const char	*ret_token_literal(enum e_token_type n);
void		print_token_list_minimal(t_token *tok);

/* t_tree.c */

t_tree		*tree_factory(t_tree *blueprint);

/* t_tree_print.c */

void		auto_print_tree(t_tree *tree);
void		print_tree(t_pos p, t_tree *tree);

/* t_word_lst.c */

t_word_lst	*word_lst_factory(t_word_lst *blueprint);
t_list		*list_factory(t_list *blueprint);

#endif
