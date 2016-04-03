/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 13:53:56 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/03 15:32:52 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "option.h"
#include "randgen.h"

t_opt				g_opts[] = {
	{2, {"-v", "--verbose"}, 1, {"shows additionnal messages."}, FLAG_VERBOSE, activate_flag},
	{3, {"-0", "-c", "--column"}, 1, {"activates single column display"}, FLAG_ONE_COL, activate_flag},
	{2, {"-f", "--float"}, 1, {"activates floating point numbers"}, FLAG_FLOAT, activate_flag}
};

unsigned int		g_flags = FLAG_DEFAULT;

int					activate_flag(t_opt *opt)
{
	g_flags |= opt->flag;
	return (0);
}

int					usage(char const *app_name)
{
	static char const		help_fmt[] = "usage: %s <count=%d> [min=%.2f] [max=%.2f]\n"
		"\tgenerates <count> random numbers, in the range [min,max]\n%s";
	static char				opts_fmt[1024];
	int						buflen, len;
	int						i, j;

	snprintf(opts_fmt, 1024, "\noptions:\n");
	len = (int)(sizeof(g_opts) / sizeof(t_opt));
	i = 0;
	buflen = 0;
	while (i < len && buflen < 1024)
	{
		buflen += snprintf(&opts_fmt[buflen], 1024 - buflen, "\t%s\n", g_opts[i].names[0]);
		j = 0;
		while (j < g_opts[i].num_desc_lines && buflen < 1024)
		{
			buflen += snprintf(&opts_fmt[buflen], 1024 - buflen, "\t\t%s\n", g_opts[i].desc_lines[j]);
			j++;
		}
		i++;
	}
	i = 0;
	if (g_flags & FLAG_VERBOSE)
		i = printf("Starting randgen v%s\n\tCreated by %s (aka %s)\n",
				   VERSION_STRING, AUTHOR_NAME, AUTHOR_PSEUDO);
	return ((i += printf(help_fmt, app_name, DFLT_GEN_COUNT, DFLT_GEN_MIN, DFLT_GEN_MAX, opts_fmt)));
}

t_opt						*option_find(char const *name)
{
	t_opt					*opt;
	int						i;
	int						j;

	i = sizeof(g_opts) / sizeof(t_opt);
	while (i--)
	{
		opt = &g_opts[i];
		j = 0;
		while (j < opt->num_names)
		{
			if (!strcmp(opt->names[j], name))
				return (opt);
			j++;
		}
	}
	return (NULL);
}
