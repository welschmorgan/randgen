/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 13:55:04 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/03 13:58:00 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPTION_H
# define	OPTION_H

# define NAME_ALIAS_COUNT	4
# define NAME_SIZE			20
# define DESC_LINES_COUNT	10
# define DESC_LINE_SIZE		120

# define DFLT_GEN_COUNT		50
# define DFLT_GEN_MIN		0.0f
# define DFLT_GEN_MAX		100.0f

typedef enum				e_flag
{
	FLAG_NONE,
	FLAG_VERBOSE = 1 << 1,
	FLAG_ONE_COL = 1 << 2,
	FLAG_FLOAT = 1 << 3,
	FLAG_COUNT = 3,
	FLAG_DEFAULT = FLAG_NONE,
}							t_flag;

typedef struct				s_opt
{
	unsigned char			num_names;
	char					names[NAME_ALIAS_COUNT][NAME_SIZE];
	unsigned char			num_desc_lines;
	char					desc_lines[DESC_LINES_COUNT][DESC_LINE_SIZE];
	t_flag					flag;
	int						(*func)(struct s_opt *opt);
}							t_opt;

int							activate_flag(t_opt *opt);

t_opt						*option_find(char const *name);

extern t_opt				g_opts[];
extern unsigned int			g_flags;

int							usage(char const *app_name);

#endif
