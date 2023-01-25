/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:34 by znichola          #+#    #+#             */
/*   Updated: 2023/01/25 14:55:06 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <termios.h>

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

int			exec_echo(char **args, t_env **env, int prev);
int			exec_pwd(char **args, t_env **env, int prev);
int			exec_exit(char **args, t_env **env, int prev);
int			exec_env(char **args, t_env **env, int prev);
int			exec_export(char **args, t_env **env, int prev);
int			exec_unset(char **args, t_env **env, int prev);
int			exec_cd(char **args, t_env **env, int prev);

/* custom */
int			exec_shout(char **args, t_env **env, int prev);

/* ************************************************************************** */
/*   environment                                                              */
/* ************************************************************************** */

/* environment.c */

t_env		*init_env(char **envp);
char		**env_to_strarr(t_env *env);
char		*ret_env_key(t_env *env, char *key);
int			is_valid_identifier(char *str);

/* env_utils.c */
size_t		size_env(t_env *env);
void		env_add(t_env **env, char *key, char *value);
void		env_remove(t_env **env, char *key);

/* env_sort.c */
void		sort_env(t_env **env);

/* ************************************************************************** */
/*   exicution                                                                */
/* ************************************************************************** */

/* exec pipeline */
int			exec_pipeline(t_pipeline *p, t_env **env, int prev);

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

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n, t_env *env);

/* prepare fds */

t_fds		*prepare_fds(int n);
void		cleanup_fds(t_fds *fds, int n_cmds);

/* exec_utils */

int			compute_return_value(int status);
int			redirect(int input_fd, int output_fd);

/* multi_cmds.c */

int			multiple_commands(t_cmd *cmds, t_fds *fds, int n, t_env *env, int prev);
int			*launch_all(t_cmd_info *cmds, t_fds *fds, int n, t_env *env, int prev);

/* simple_cmd_exec.c */

int			simple_command(t_cmd *cmd, t_fds *fds, t_env **env, int prev);

/* exec_builtin.c */

int			ret_builtin_enum(char *str);
const char	*ret_builtin_literal(enum e_builtin n);
int			exec_builtin(enum e_builtin n, char **args, t_env **env, int prev);

/* launch_builtin.c */
int			launch_builtin(t_cmd_info *cmd, t_fds *fds, t_env **env, int prev);

/* ************************************************************************** */
/*   expansion                                                                */
/* ************************************************************************** */

/* expansion */

int			expand_pipeline(t_pipeline **p, t_parsed_pipeline *intermediate, t_env *env, int retn);
int			expand_cmd(t_cmd *definitive, t_parsed_cmd *intermediate, t_env *env, int retn);

/* var_exp */

char		**variable_expansion(char *str);

/* wild_exp */

char		*wildcard_expansion(char *str);

/* quote_removal.c */

char		*quote_removal(char *str);

/* param_expansion */

char		*param_expansion(char *str, t_env *env, int retn);

/* field split */
t_list		*field_split(char *str);

/* expansion2 */

t_list		*expand_args_list(t_list *lst, t_env *env, int retn);
int			expand_redirs(t_list *redirs, t_env *env, int retn);

/* ************************************************************************** */
/*   parsing                                                                  */
/* ************************************************************************** */

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

/* token_list.c */

void		next_token(t_token **list);
int			construct_tok_list(t_token **lst, char *str);
void		tok_list_cleanup(t_token *lst);

/* tokenizer */
int			lexer(t_token **tok, char **str);

/* ************************************************************************** */
/*   utils                                                                    */
/* ************************************************************************** */

void		*x_malloc(size_t size, size_t quantity);
int			ft_isspace(int c);
void		do_nothing(void *thing);
void		strarr_cleanup(char **s);
void		strarr_print(char **s);

char		*list_to_str(t_list *word);
void		words_print(t_list *word);

/* tree_ops */

int			get_tree_width(t_tree *tree, int level);
int			get_tree_height(t_tree *tree);
int			get_tree_max_width(t_tree *tree);

/* error_printer.c */

void		print_error(char *program, char *arg, char *msg);
char		*in_quotes(char *str);

/* ************************************************************************** */
/*   utils                                                                    */
/* ************************************************************************** */

/* signals.c */

void	sigint_handler(int sig);
void	parent_signals(void);
void	get_set_termios(int toggle);
void	silent_signals(void);
void	pipe_return_print(int retn);

/* ************************************************************************** */
/*   structs                                                                  */
/* ************************************************************************** */

/* t_pipeline */

void		print_pipeline(t_pipeline *p);
void		pipeline_cleanup(t_pipeline *p);

/* t_parsed_pipeline */

t_parsed_pipeline	*parsed_pipeline_factory(t_parsed_pipeline *blueprint);
void				parsed_pipeline_cleanup(t_parsed_pipeline *p);
void				print_parsed_pipeline(t_parsed_pipeline *p);

/* t_cmd_info.c */

void				cleanup_all_info(t_cmd_info *infos, int n);
void				init_info(t_cmd_info *info, t_cmd *cmd, int i, int n);

/* t_parsed_cmd.c */

t_parsed_cmd	*parsed_cmd_factory(t_parsed_cmd *blueprint);
void			parsed_cmd_cleanup(t_parsed_cmd *cmd);
void			print_parsed_cmd(t_parsed_cmd *cmd);
void			print_parsed_cmd2(t_parsed_cmd *cmd);

/* t_cmd.c */

t_cmd		*cmd_factory(t_cmd *blueprint);
void		print_cmd(t_cmd *cmd);
void		cmd_cleanup(t_cmd *cmd);

/* t_fds.c */

void		close_fds(t_fds *fds, int n);

/* t_token.c */

t_token		*token_factory(t_token *next, char *str, enum e_token_type type);
void		token_cleanup(t_token *tok);
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
void		env_cleanup(t_env *env);
void		env_cleanup_all(t_env *env);

#endif
