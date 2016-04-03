/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 13:31:36 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/03 15:10:33 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		NODE_H
# define	NODE_H

typedef struct		s_node
{
	struct s_node	*next;
	void			*data;
	unsigned		size;
}					t_node;

t_node				*node_back(t_node *n, unsigned nth);
t_node				*node_new(void *data);
t_node				*node_push(t_node **n, t_node *pushed);
t_node				*node_set(t_node *n, t_node *next, void *data);
t_node				*node_reset(t_node *n);
t_node				*node_delete(t_node **node);
t_node				*node_get(t_node *node, unsigned nth);
void				node_delete_all(t_node **node);
unsigned			node_size(t_node *n);

#endif










