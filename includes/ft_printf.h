/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:21:08 by znichola          #+#    #+#             */
/*   Updated: 2023/01/23 19:16:24 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>

// # include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>

# define DECIM "0123456789"
# define HEX_S "0123456789abcdef"
# define HEX_X "0123456789ABCDEF"
# define CNV "cspdiuxX%"
# define FLG "-+#0 "

# define SUCCESS 0
# define FAILIUR 1
# define UNSET -1
/* Modidifer flangs as big representatoin, see the musl implementaion*/

////// START with a %
// # define HASH	(1U << 0) // alternate form for x X conversion
// # define ZERO	(1U << 1)
		// 0 padding for all converions. if presicion is given ignore
// # define MINUS	(1U << 2) // the value is to be left adjusted
// # define SPACE	(1U << 3) // a blank left before signed conversion
// # define PLUS	(1U << 4) // always place sign before numer,
		// overrides space is both used
// apostrof, not manditory but cool, seperates nums into groups of 3
// MANDETORY optional decimal number for minimum field width etc
// # define PERIOD	(1U << 5)
		// a period followed by optional digic string for min
		// number of digits to appear or max character printed
// optional length modifier l ll etc.
////// END with a character that spesifies the converion type

// %[flags][width][.precision][length]specifier

// # define SPACE	(1U << (' ' - 32))
// # define HASH	(1U << ('#' - 32))
// # define PLUS	(1U << ('+' - 32))
// # define MINUS	(1U << ('-' - 32))
// // # define PERIOD	(1U << ('.' - 32))
// # define ZERO	(1U << ('0' - 32))

// # define FLAG_MASK (SPACE | HASH | PLUS | MINUS | ZERO)

# define FT_SPACE 1U
# define FT_HASH 8U
# define FT_PLUS 2048U
# define FT_MINUS 8192U
# define FT_PERIOD 16384U
# define FT_ZERO 65536U
# define FLAG_MASK 92169U

// # define CHR (1UL << ('c' - 'X'))
// # define STR (1UL << ('s' - 'X'))
// # define PRT (1UL << ('p' - 'X'))
// # define DEC (1UL << ('d' - 'X'))
// # define INT (1UL << ('i' - 'X'))
// # define USI (1UL << ('u' - 'X'))
// # define HES (1UL << ('x' - 'X'))
// # define HEX (1UL << ('X' - 'X'))

// # define CHR (1U << 1) // 0000 0000 0000 0000  0000 0000 0000 0010
// # define STR (1U << 2) // 0000 0000 0000 0000  0000 0000 0000 0100
// # define PRT (1U << 3) // 0000 0000 0000 0000  0000 0000 0000 1000
// # define DEC (1U << 4) // 0000 0000 0000 0000  0000 0000 0001 0000
// # define INT (1U << 5) // 0000 0000 0000 0000  0000 0000 0010 0000
// # define USI (1U << 6) // 0000 0000 0000 0000  0000 0000 0100 0000
// # define HES (1U << 7) // 0000 0000 0000 0000  0000 0000 1000 0000
// # define HEX (1U << 8) // 0000 0000 0000 0000  0000 0001 0000 0000
// # define PCT (1U << 9) // 0000 0000 0000 0000  0000 0010 0000 0000
// 					   // 0000 0000 0000 0000  0000 0011 1111 1111
// # define CNV_MASK (CHR | STR | PRT | DEC | INT | USI | HES | HEX)

# define CHR 2U
# define STR 4U
# define PRT 8U
# define DEC 16U
# define INT 32U
# define USI 64U
# define HES 128U
# define HEX 256U
# define PCT 512U

# ifdef DEBUG
#  define DEBUG_TEST 1
# else
#  define DEBUG_TEST 0
# endif

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_arg
{
	long			i;
	unsigned long	u;
	void			*p;
	int				flags;
	int				cnv;
	int				width;
	int				precision;
	int				nlen;
	int				sign;
	int				fd;
	int				zeros;
	t_bool			write;
}	t_arg;

int		ft_p_pad(t_arg *arg);
int		ft_p_prefix(t_arg *arg);
int		ft_p_suffix(t_arg *arg);

void	ft_p_falgs(t_arg *arg, const char **fmt);
void	ft_p_width(t_arg *arg, const char **fmt);
void	ft_p_precision(t_arg *arg, const char **fmt);
int		ft_p_specifier(t_arg *arg, va_list *ap);
int		ft_p_write_cnv(t_arg *arg);

int		ft_p_wwrite(t_arg *arg, const void *s, int l);
int		ft_p_write_zeros(t_arg *arg);
int		ft_p_write_padzeros(t_arg *arg);
int		ft_p_w_char(t_arg *arg);
int		ft_p_w_str(t_arg *arg);
int		ft_p_w_int(t_arg *arg);
int		ft_p_w_ptr(t_arg *arg);
int		ft_p_w_uin(t_arg *arg);

int		ft_count_lldigits(unsigned int base, long long n);
int		ft_count_ulldigits(unsigned int base, unsigned long long n);
int		ft_p_ultoa_base_write(t_arg *arg, unsigned long n, char *bstr);
int		ft_p_ltoa_base_write(t_arg *arg, long long n, char *bstr);
int		ft_p_str_chunk(int fd, const char **fmt);
int		ft_p_formatted_chunk(int fd, const char **fmt, va_list *ap);
int		ft_printf(const char *format, ...);
int		ft_printfd(int fd, const char *format, ...);
int		ft_debug_printf(int fd, const char *format, ...);

// LIBFT
int		ft_p_isin(char c, char *s);
size_t	ft_p_strlen(const char *s);
int		ft_p_isdigit(int c);

#endif /* ft_printf_h */
