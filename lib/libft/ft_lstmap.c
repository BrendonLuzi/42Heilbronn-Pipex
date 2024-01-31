/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:22:04 by bluzi             #+#    #+#             */
/*   Updated: 2022/11/21 23:21:56 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*comp;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		comp = ft_lstnew(f(lst -> content));
		if (!comp)
		{
			ft_lstclear(&new_lst, del);
			ft_lstclear(&comp, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, comp);
		lst = lst -> next;
	}
	return (new_lst);
}
