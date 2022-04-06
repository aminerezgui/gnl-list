/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezgui <arezgui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:49:09 by arezgui           #+#    #+#             */
/*   Updated: 2022/04/08 14:49:12 by arezgui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(1 * sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_list;

	if (!lst)
		return ;
	current_list = *lst;
	if (!current_list)
		*lst = new;
	else
	{
		while (current_list->next)
			current_list = current_list->next;
		current_list->next = new;
	}
}

int	ft_lstsize(t_list *lst)
{
	t_list	*current_node;
	int		lst_len;

	current_node = lst;
	lst_len = 0;
	if (!current_node)
		return (lst_len);
	while (current_node->next)
	{
		lst_len++;
		current_node = current_node->next;
	}
	lst_len++;
	return (lst_len);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*current_node;

	current_node = lst;
	if (!current_node)
		return ;
	del(current_node->content);
	free(current_node);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current_node;
	t_list	*current_node_to_free;

	if (!lst)
		return ;
	current_node = *lst;
	if (!current_node)
		return ;
	while (current_node->next)
	{
		current_node_to_free = current_node;
		current_node = current_node->next;
		ft_lstdelone(current_node_to_free, del);
	}
	ft_lstdelone(current_node, del);
	*lst = NULL;
}
