/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_50_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 12:20:33 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/03 15:22:21 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "randgen.h"
#include "node.h"
#include "option.h"

int					randgen(int ngen, float const min, float const max)
{
	static float	fnum;
	static int		num;

	if (g_flags & FLAG_VERBOSE)
		printf("Generating %d numbers, between %.2f and %.2f...\n", ngen, min, max);
	while (ngen--)
	{
		if (g_flags & FLAG_FLOAT)
		{
			fnum = ((float)rand()/(float)(RAND_MAX)) * max + min;
			printf("%f\n", fnum);
		}
		else
		{
			num = (rand() % (int)max) + (int)min;
			printf("%d\n", num);
		}
	}
	return (0);
}

int					option_parse(int argc, char *argv[], t_node **free_args)
{
	char			**parg;
	t_opt			*opt;
	int				code;

	argc = 0;
	parg = &argv[1];
	code = 0;
	while (parg && *parg && !code)
	{
		if ((opt = option_find(*parg)))
		{
			if ((code = opt->func(opt)))
			{
				printf("error: failed to activated option '%s'\n", opt->names[0]);
				break ;
			}
		}
		else if ((code = !strncmp(*parg, "-", 1)
				  || (code = !strncmp(*parg, "--", 2))))
		{
			printf("%s: unknown option!\n", *parg);
			break;
		}
		else
			node_push(free_args, node_new(*parg));
		parg++;
		argc++;
	}
	return (code);
}

int					main(int argc, char *argv[])
{
	static int		ngen = DFLT_GEN_COUNT;
	static float	min = DFLT_GEN_MIN, max = DFLT_GEN_MAX;
	int				code;
	t_node			*cur;
	unsigned		sz;
	static t_node	*free_args = NULL;

	code = option_parse(argc, argv, &free_args);
	if (code != 0)
	{
		node_delete_all(&free_args);
		return (-1);
	}
	sz = node_size(free_args);
	if (sz >= 1)
	{
		cur = node_back(free_args, 1);
		ngen = atoi((char*)cur->data);
		if (sz >= 2)
		{
			if (sz < 3)
				return (usage(argv[0]));
			cur = node_back(free_args, 2);
			if (g_flags & FLAG_VERBOSE)
				printf("Lower bound: %s\n", (char*)cur->data);
			min = strtof((char*)cur->data, NULL);
			cur = node_back(free_args, 3);
			if (g_flags & FLAG_VERBOSE)
				printf("Upper bound: %s\n", (char*)cur->data);
			max = strtof((char*)cur->data, NULL);
		}
	}
	else if (sz < 1 || sz > 3 || ngen < 1)
	{
		node_delete_all(&free_args);
		return (usage(argv[0]));
	}
	srand(time(NULL));
	if (g_flags & FLAG_VERBOSE)
		printf("Starting randgen v%s\n\tCreated by %s (aka %s)\n\n",
			   VERSION_STRING, AUTHOR_NAME, AUTHOR_PSEUDO);
	code = randgen(ngen, min, max);
	node_delete_all(&free_args);
	return (code);
}
