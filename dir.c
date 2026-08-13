/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:54:37 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 17:55:01 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_dot_dir(char *name)
{
	if (name[0] == '.' && name[1] == '\0')
		return (1);
	if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (1);
	return (0);
}

void	add_entry(char *path, char *name, t_list **files)
{
	struct stat	info;
	t_file		*f;
	char		*full;

	f = malloc(sizeof(t_file));
	full = build_path(path, name);
	if (lstat(full, &info) != -1)
	{
		fill_file(f, ft_strdup(name), &info);
		if (S_ISLNK(info.st_mode))
			f->link = read_link(full);
		ft_lstadd_back(files, ft_lstnew(f));
	}
	else
		free(f);
	free(full);
}

void	read_entries(DIR *dir, char *path, int *flags, t_list **files)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (flags[FLAG_A] || entry->d_name[0] != '.')
			add_entry(path, entry->d_name, files);
		entry = readdir(dir);
	}
}

void	recurse_subdirs(char *path, t_list *files, int *flags, int *printed)
{
	t_file	*f;
	char	*child;

	while (files)
	{
		f = files->content;
		if (S_ISDIR(f->mode) && !is_dot_dir(f->file_name))
		{
			child = build_path(path, f->file_name);
			list_dir(child, flags, 1, printed);
			free(child);
		}
		files = files->next;
	}
}

void	list_dir(char *path, int *flags, int header, int *printed)
{
	DIR		*dir;
	t_list	*files;

	if (header)
		print_header(path, printed);
	dir = opendir(path);
	if (!dir)
	{
		print_error(path);
		return ;
	}
	files = NULL;
	read_entries(dir, path, flags, &files);
	closedir(dir);
	sort_list(files, flags);
	*printed = 1;
	printfiles(files, flags[FLAG_L], 1);
	if (flags[FLAG_R_BIG])
		recurse_subdirs(path, files, flags, printed);
	ft_lstclear(&files, free_file);
}
