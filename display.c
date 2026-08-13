/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:55:26 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 17:55:29 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_widths(t_list *files, t_width *w)
{
	t_file	*f;
	int		len;

	w->nlink = 0;
	w->owner = 0;
	w->group = 0;
	w->size = 0;
	while (files)
	{
		f = files->content;
		len = num_width(f->nlink);
		if (len > w->nlink)
			w->nlink = len;
		len = ft_strlen(owner_name(f->uid));
		if (len > w->owner)
			w->owner = len;
		len = ft_strlen(group_name(f->gid));
		if (len > w->group)
			w->group = len;
		len = num_width(f->size);
		if (len > w->size)
			w->size = len;
		files = files->next;
	}
}

long	get_total(t_list *files)
{
	long	total;
	t_file	*f;

	total = 0;
	while (files)
	{
		f = files->content;
		total += f->blocks;
		files = files->next;
	}
	return (total);
}

void	print_long(t_file *file, t_width w)
{
	char	*ow;
	char	*gr;
	char	*t;

	print_perms(file);
	print_pad(w.nlink - num_width(file->nlink) + 1);
	ft_printf("%d ", file->nlink);
	ow = owner_name(file->uid);
	ft_printf("%s", ow);
	print_pad(w.owner - ft_strlen(ow) + 2);
	gr = group_name(file->gid);
	ft_printf("%s", gr);
	print_pad(w.group - ft_strlen(gr) + 2);
	print_pad(w.size - num_width(file->size));
	ft_printf("%ld ", file->size);
	t = ctime(&file->mtime);
	ft_printf("%.12s ", t + 4);
	ft_printf("%s", file->file_name);
	if (file->link)
		ft_printf(" -> %s", file->link);
	ft_printf("\n");
}

void	printfiles(t_list *targets, int extended_print, int show_total)
{
	t_list	*tmp;
	t_file	*file;
	t_width	w;

	tmp = targets;
	get_widths(targets, &w);
	if (extended_print && show_total)
		ft_printf("total %ld\n", get_total(targets));
	while (tmp)
	{
		file = tmp->content;
		if (extended_print)
			print_long(file, w);
		else
			ft_printf("%s\n", file->file_name);
		tmp = tmp->next;
	}
}
