/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:56:30 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 17:56:33 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	cmp_name(t_file *a, t_file *b)
{
	size_t	la;
	size_t	lb;
	size_t	n;

	la = ft_strlen(a->file_name);
	lb = ft_strlen(b->file_name);
	if (la > lb)
		n = la;
	else
		n = lb;
	return (ft_strncmp(a->file_name, b->file_name, n + 1));
}

int	cmp_time(t_file *a, t_file *b)
{
	if (a->mtime < b->mtime)
		return (1);
	if (a->mtime > b->mtime)
		return (-1);
	if (a->mtime_nsec < b->mtime_nsec)
		return (1);
	if (a->mtime_nsec > b->mtime_nsec)
		return (-1);
	return (cmp_name(a, b));
}

void	swap_content(t_list *a, t_list *b)
{
	void	*value;

	value = a->content;
	a->content = b->content;
	b->content = value;
}

void	sort_files(t_list *list, int (*cmp)(t_file *, t_file *), int rev)
{
	int		swapped;
	t_list	*tmp;
	int		c;

	swapped = 1;
	if (!list)
		return ;
	while (swapped)
	{
		swapped = 0;
		tmp = list;
		while (tmp->next)
		{
			c = cmp(tmp->content, tmp->next->content);
			if (rev)
				c = -c;
			if (c > 0)
			{
				swap_content(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}

void	sort_list(t_list *list, int *flags)
{
	if (flags[FLAG_T])
		sort_files(list, cmp_time, flags[FLAG_R]);
	else
		sort_files(list, cmp_name, flags[FLAG_R]);
}
