/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:33 by znichola          #+#    #+#             */
/*   Updated: 2022/12/02 17:23:31 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

// #define MAIN

// # ifdef MAIN
// #  define PRINT
// #  define BUFFER_SIZE 13
// # endif /* main */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define DELIM '\n'

typedef enum e_action
{
	initialise,
	liberate
}		t_action;

# define LINE_FOUND 1U
# define END_OF_FILE 2U
# define LINE_INCOMPLETE 4U
# define MALLOC_ERROR 8U

typedef struct s_rest
{
	char	*root;
	char	*seek;
}	t_rest;

/* get_net_line */
char	*ft_get_next_line(int fd);
char	*get_next_line(int fd);

/* gnl_utils */
void	*ft_gnl_calloc(size_t nmemb, size_t size);
char	*ft_gnl_strchr(const char *s, int c);
void	ft_gnl_bzero(void *s, size_t n);
char	*ft_gnl_strmerg(char *rest, char *buff);

char	*ft_gnl_buffmerg(char *s, char *buff);

#endif /* get_next_line*/
