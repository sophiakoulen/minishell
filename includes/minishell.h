/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:34 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 14:55:41 by znichola         ###   ########.fr       */
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

int			exec_echo(char **args);
int			exec_pwd(char **args);
int			exec_exit(char **args);

int			exec_env(char **args);
t_env		*init_env(char **envp);
char		**env_to_strarr(t_env *env);
char		*ret_env_key(t_env *env, char *key);

/* ************************************************************************** */
/*   exicution                                                                */
/* ************************************************************************** */

/* exec pipeline */
int			exec_pipeline(t_pipeline *p);

/* heredoc */

void		do_all_heredocs(t_cmd_info *infos, int **hd_pipes, int n);

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

/* multi_cmds.c */

int			multiple_commands(t_cmd *cmds, t_fds *fds, int n);
int			*launch_all(t_cmd *cmds, t_cmd_info *infos, t_fds *fds, int n);

/* simple_cmd_exec.c */

int			simple_cmd_exec(t_cmd *cmds, t_fds *fds);

/* exec_builtin.c */

int			ret_builtin_enum(char *str);
const char	*ret_builtin_literal(enum e_builtin n);
int			exec_builtin(enum e_builtin n, char **args);

/* ************************************************************************** */
/*   expansion                                                                */
/* ************************************************************************** */

/* expansion */
t_pipeline	*expand_pipeline(t_parsed_pipeline *intermediate);
void		expand_cmd(t_cmd *definitive, t_parsed_cmd *intermediate);

/* var_exp */

char		**variable_expansion(char *str);

/* wild_exp */

char		*wildcard_expansion(char *str);

/* ************************************************************************** */
/*   parsing                                                                  */
/* ************************************************************************** */

/* prs comandline */

int			parse_commandline(t_tree **tree, t_token *tok);

/* prs pipeline */

int			parse_pipeline(t_parsed_pipeline *pipeline, t_token **tok);

/* prs command */

int			parse_cmd(t_parsed_cmd **cmd, t_token **tok);

/* prs item */

int			parse_item(t_item **item, t_token **tok);

/* parse errors */
int			unexpected_token(t_token *tok);
int			assert_token(t_token *tok, enum e_token_type expected);


t_cmd		*cmd_factory(t_cmd *blueprint);

/* ************************************************************************** */
/*   tokenizer                                                                */
/* ************************************************************************** */

/* tokenizer */

t_token		*construct_tok_list(char *str);
void		tok_list_cleanup(t_token *lst);

/* ************************************************************************** */
/*   utils                                                                    */
/* ************************************************************************** */

void		*x_malloc(size_t size, size_t quantity);
int			ft_isspace(int c);
void		do_nothing(void *thing);
void		strarr_cleanup(char **s);
void		strarr_print(char **s);

/* tree_ops */

int			get_tree_width(t_tree *tree, int level);
int			get_tree_height(t_tree *tree);
int			get_tree_max_width(t_tree *tree);

/* ************************************************************************** */
/*   structs                                                                  */
/* ************************************************************************** */

/* t_pipeline */
void		print_pipeline(t_pipeline *p);
void		pipeline_cleanup(t_pipeline *p);

/* t_cmd_info.c */

// nothing yet

/* t_parsed_cmd.c */

t_parsed_cmd	*parsed_cmd_factory(t_parsed_cmd *blueprint);
void			parsed_cmd_cleanup(t_parsed_cmd *cmd);
void			print_parsed_cmd(t_parsed_cmd *cmd);

/* t_cmd.c */

t_cmd		*cmd_factory(t_cmd *blueprint);
void		print_cmd(t_cmd *cmd);
void		cmd_cleanup(t_cmd *cmd);

/* t_fds.c */

void		close_fds(t_fds *fds, int n);

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

/* t_item.c */

t_item		*item_factory(t_item *blueprint);
void		item_cleanup(t_item *item);
void		item_cleanup_deep(t_item *item);
void		print_item(t_item *item);

/* t_env.c */

t_env		*env_factory(t_env *blueprint);
size_t		size_env(t_env *env);
void		env_cleanup(t_env *env);

#endif
