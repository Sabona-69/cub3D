/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:34:17 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:34:19 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_list	*new_node(void	*ptr)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

t_list	*last_node(t_list **head)
{
	t_list	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_list	**head, t_list *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
		last_node(head)->next = new;
}

void	clear_all(t_list **head)
{
	t_list	*cur;
	t_list	*tmp;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->ptr);
		cur->ptr = NULL;
		free(cur);
		cur = tmp;
	}
	*head = NULL;
}

void	*ft_malloc(size_t size, t_call call)
{
	static t_list	*head;
	t_list			*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
			(clear_all(&head), exit(1));
		tmp = new_node(ptr);
		if (!tmp)
			(clear_all(&head), free(ptr), exit(1));
		add_back(&head, tmp);
		ft_bzero(ptr, size);
		return (ptr);
	}
	else if (call == FREE)
		clear_all(&head);
	return (NULL);
}
