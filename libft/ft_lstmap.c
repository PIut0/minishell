/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 03:45:03 by klim              #+#    #+#             */
/*   Updated: 2020/12/28 01:03:15 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
	void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;
	t_list	*new;

	if (!lst || !f)
		return (0);
	if (!(ret = ft_lstnew(f(lst->content))))
		return (0);
	tmp = ret;
	lst = lst->next;
	while (lst)
	{
		if (!(new = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		tmp->next = new;
		tmp = new;
		lst = lst->next;
	}
	return (ret);
}
