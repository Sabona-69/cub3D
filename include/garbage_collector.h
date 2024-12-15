/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:33:48 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 17:39:14 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_list
{
	void			*ptr;
	struct s_list	*next;
}	t_list;

typedef enum e_call
{
	FREE,
	MALLOC
}	t_call;

t_list	*new_node(void	*ptr);
t_list	*last_node(t_list **head);
void	add_back(t_list	**head, t_list *new);
void	clear_all(t_list **head);
void	*ft_malloc(size_t size, t_call call);
#endif