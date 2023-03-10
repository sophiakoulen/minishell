/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:34 by znichola          #+#    #+#             */
/*   Updated: 2023/02/16 19:56:43 by skoulen          ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>

# include "libft.h"
# include "defines.h"
# include "structs.h"

/* cleanup */

void		tree_cleanup(t_tree *tree);
void		pipeline_cleanup(t_list *pipeline);

/* print */

void		print_pipeline(t_list *lst);
void		print_cmd(t_item *lst);

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

/* builtin */

int			launch_builtin(t_exec *exec, int i);
int			ret_builtin_enum(char *str);

/* exec_pipeline */

int			exec_tree(t_tree *tree, t_env **env, int prev);

/* exec_pipeline2 */

int			cmds_with_forks(t_exec *exec);
int			*launch_all(t_exec *exec);

/* exec_utils */

int			compute_return_value(int status);
int			redirect(int input_fd, int output_fd);
void		close_fds(t_exec *exec);

/* find_cmd */

int			find_cmd(char **path, char *filename, char **res);

/* heredoc */

void		read_single_heredoc(char **buffer, char *delim);
void		write_all_heredocs(t_exec *exec);

/* prep_pipeline1 */

t_exec		*prepare_pipeline(t_list *pipeline, t_env **env, int prev);

/* prep_utils */

void		init_exec(t_list *pipeline, t_exec *exec, t_env **env, int prev);
char		**extract_args(t_item *lst);
void		prepare_cmd_path(t_cmd *cmd, t_exec *exec);

/* minitree.c */

int			minitree(char **args, t_env **env, int prev);

/* ************************************************************************** */
/*   expansion                                                                */
/* ************************************************************************** */

/* expansion */

int			expand_pipeline(t_list **pipeline, t_env *env, int retn);

/* quote_removal.c */

char		*quote_removal(char *str);

/* param_expansion */

char		*param_expansion(char *str, t_env *env, int retn);

/* field split */

t_item		*field_split(t_item *item);

/* expansion utils */

int			update_state(char *c, int *state);
char		*escape_special_chars(char *str, int flag);

/* wildcard_exp.c */

void		find_wildcard_matches(char **ret, char *str);
void		expand_wildcards(t_item **res, t_item *items);
char		**wild_split(char const *s, char c);
int			match_wildcard(char *file, char *expr);

/* ************************************************************************** */
/*   parsing                                                                  */
/* ************************************************************************** */

/* prs tree */

int			parse_tree(t_tree **tree, t_token **tok);

/* prs pipeline */

int			parse_pipeline(t_list **pipeline, t_token **tok);

/* prs command */

int			parse_cmd(t_item **cmd, t_token **tok);

/* prs item */

int			parse_item(t_item **item, t_token **tok);

/* parse errors */

int			unexpected_token(t_token *tok);
int			assert_token(t_token *tok, enum e_token_type expected);

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
char		*ft_strmerge(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);

/* tree_ops */

int			get_tree_width(t_tree *tree, int level);
int			get_tree_height(t_tree *tree);
int			get_tree_max_width(t_tree *tree);

/* error_printer.c */

void		print_error(char *program, char *arg, char *msg);
char		*in_quotes(char *str);

/* input */

char		*get_input_line(char *prompt);

/* lst_sort */

t_list		*lst_swap(t_list *a, t_list *b);
void		lst_bubble_sort(t_list **lst, int (c)(const char *, const char *));

/* safe_atoi.c */

int			safe_atoi(int *n, char **str);
int			safe_multi(int *a, int b);
int			safe_add(int *a, int b);

/* ************************************************************************** */
/*   signals                                                                  */
/* ************************************************************************** */

/* signals.c */

void		sigint_handler(int sig);
void		parent_signals(void);
void		get_set_termios(int toggle);
void		silent_signals(void);
void		print_pipe_error(int n);

/* ************************************************************************** */
/*   structs                                                                  */
/* ************************************************************************** */

/* t_cmd.c */

void		cmd_cleanup(t_cmd *cmd);

/* t_token.c */

t_token		*token_factory(t_token *next, char *str, enum e_token_type type);
void		token_cleanup(t_token *tok);
const char	*ret_token_literal(enum e_token_type n);
void		print_token_list_minimal(t_token *tok);

/* t_tree.c */

t_tree		*tree_factory(int type, t_tree *lhs, t_tree *rhs, t_list *pipeline);

/* t_tree_print.c */

void		print_minitree(t_tree *root, t_trunk *prev, int isright, int opts);

/* t_item.c */

t_item		*item_factory(t_item *blueprint);
void		item_list_cleanup(t_item *lst);
void		print_item(t_item *item);
void		print_cmd(t_item *item);

/* t_env.c */

t_env		*env_factory(char *key, char *value, t_env *next);
void		env_cleanup(t_env *env);
void		env_cleanup_all(t_env *env);
t_env		*env_last(t_env *env);

/* t_exec */

void		cleanup_exec(t_exec *exec);

/* t_trunk.c */

t_trunk		*trunk_factory(t_trunk *blueprint);
void		trunk_print(t_trunk *t);
void		trunk_garbage_collector(t_trunk *trunk);

#endif
