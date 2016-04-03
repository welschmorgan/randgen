/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 13:31:40 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/03 15:15:22 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include <stdlib.h>

unsigned			node_size(t_node *n)
{
	unsigned		sz;

	sz = 0;
	while (n)
	{
		sz++;
		n = n->next;
	}
	return (sz);
}

t_node				*node_push(t_node **n, t_node *pushed)
{
	if (!n || !pushed)
		return (NULL);
	pushed->next = *n;
	*n = pushed;
	return (*n);
}

t_node				*node_new(void *data)
{
	t_node			*nu;

	nu = (t_node*)malloc(sizeof(t_node));
	return (node_set(nu, NULL, data));
}

void				node_delete_all(t_node **node)
{
	if (!node)
		return ;
	while (*node)
		*node = node_delete(node);
}

t_node				*node_delete(t_node **node)
{
	t_node			*next;

	if (!node)
		return (NULL);
	if (!*node)
		return (*node);
	next = (*node)->next;
	free(*node);
	return ((*node = next));
}

t_node				*node_set(t_node *n, t_node *next, void *data)
{
	if (!n)
		return (n);
	n->next = next;
	n->data = data;
	return (n);
}

t_node				*node_reset(t_node *n)
{
	t_node			*nxt;

	if (!n)
		return (n);
	nxt = n->next;
	n->data = NULL;
	n->next = NULL;
	return (nxt);
}

t_node				*node_back(t_node *n, unsigned nth)
{
	unsigned		sz, i;

	sz = node_size(n);
	nth = nth > sz ? sz : nth;
	i = 0;
	while (n && n->next && i++ < (sz - nth))
		n = n->next;
	return (n);
}

t_node				*node_get(t_node *node, unsigned nth)
{
	while (node && nth--)
		node = node->next;
	return (node);
}
