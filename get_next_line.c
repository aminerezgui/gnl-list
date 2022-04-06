/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezgui <arezgui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:51:06 by arezgui           #+#    #+#             */
/*   Updated: 2022/04/08 14:54:53 by arezgui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	del(void *content)
{
	free(content);
}

static void	purge_list(t_list **lst)
{
	ft_lstclear(lst, del);
	free(lst);
}

static void	extend_list_by(t_list **lst, char c_tmp)
{
	char	*content;

	content = (char *) malloc(1 * sizeof(char));
	if (!content)
		return ;
	*content = c_tmp;
	ft_lstadd_back(lst, ft_lstnew(content));
}

static char	*list_to_string(t_list **lst)
{
	char	*str;
	int		list_size;
	t_list	*current_node;

	extend_list_by(lst, '\0');
	list_size = ft_lstsize(*lst);
	str = (char *) malloc((list_size) * sizeof(char));
	current_node = *lst;
	if (!str || !current_node)
	{
		purge_list(lst);
		free(str);
		return (NULL);
	}
	while (current_node->next)
	{
		*str = *(char *)current_node->content;
		str++;
		current_node = current_node->next;
	}
	*str = *(char *)current_node->content;
	purge_list(lst);
	return (str - (list_size - 1));
}

char	*get_next_line(int fd)
{
	int		is_byte_read;
	char	c_tmp;
	t_list	**lst;

	is_byte_read = read(fd, &c_tmp, 1);
	if (is_byte_read == 1)
	{
		lst = (t_list **) malloc(1 * sizeof(t_list *));
		if (!lst)
			return (NULL);
		*lst = (NULL);
		extend_list_by(lst, c_tmp);
	}
	else
		return (NULL);
	while (is_byte_read > 0 && c_tmp != '\n')
	{
		is_byte_read = read(fd, &c_tmp, 1);
		if (is_byte_read == 1)
			extend_list_by(lst, c_tmp);
	}
	return (list_to_string(lst));
}
