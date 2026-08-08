#include "ft_ls.h"

void	print_header(char *path, int *printed)
{
	if (*printed)
		ft_printf("\n");
	ft_printf("%s:\n", path);
	*printed = 1;
}

void	add_target(char *name, t_list **files, t_list **dirs)
{
	t_file		*f;
	struct stat	info;

	if (lstat(name, &info) == -1)
	{
		print_error(name);
		return ;
	}
	f = malloc(sizeof(t_file));
	fill_file(f, ft_strdup(name), &info);
	if (S_ISLNK(info.st_mode))
		f->link = read_link(name);
	if (S_ISDIR(f->mode))
		ft_lstadd_back(dirs, ft_lstnew(f));
	else
		ft_lstadd_back(files, ft_lstnew(f));
}

void	build_targets(t_list *targets, t_list **files, t_list **dirs)
{
	while (targets)
	{
		add_target(targets->content, files, dirs);
		targets = targets->next;
	}
}

void	list_dirs(t_list *dirs, int *flags, int header, int *printed)
{
	t_file	*file;

	while (dirs)
	{
		file = dirs->content;
		list_dir(file->file_name, flags, header, printed);
		dirs = dirs->next;
	}
}

void	lister(t_list *targets, int *flags)
{
	t_list	*files;
	t_list	*dirs;
	int		header;
	int		printed;

	files = NULL;
	dirs = NULL;
	printed = 0;
	build_targets(targets, &files, &dirs);
	sort_list(files, flags);
	sort_list(dirs, flags);
	header = (files != NULL) || (ft_lstsize(dirs) > 1);
	if (files)
	{
		printfiles(files, flags[FLAG_L], 0);
		printed = 1;
	}
	list_dirs(dirs, flags, header, &printed);
	ft_lstclear(&files, free_file);
	ft_lstclear(&dirs, free_file);
}
