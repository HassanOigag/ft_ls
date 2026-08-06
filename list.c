#include "ft_ls.h"

int is_dot_dir(char *name)
{
   if (name[0] == '.' && name[1] == '\0')
      return 1;
   if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
      return 1;
   return 0;
}

void recurse_subdirs(char *path, t_list *files, int *flags, int *printed)
{
   t_list *tmp = files;

   while (tmp)
   {
      t_file *f = tmp->content;
      if (S_ISDIR(f->mode) && !is_dot_dir(f->file_name))
      {
         char *child = build_path(path, f->file_name);
         list_dir(child, flags, 1, printed);
         free(child);
      }
      tmp = tmp->next;
   }
}

void list_dir(char *path, int *flags, int header, int *printed)
{
   DIR *dir;
   struct dirent *entry;
   t_list *files = NULL;
   struct stat info;

   dir = opendir(path);
   if (!dir)
   {
      ft_printf("something happened with this dir : %s\n", path);
      return;
   }
   while ((entry = readdir(dir)))
   {
      if (!flags[FLAG_A] && entry->d_name[0] == '.')
         continue;
      t_file *f = malloc(sizeof(t_file));
      char *full = build_path(path, entry->d_name);
      if (lstat(full, &info) != -1)
      {
         fill_file(f, ft_strdup(entry->d_name), &info);
         ft_lstadd_back(&files, ft_lstnew(f));
      }
      else
         free(f);
      free(full);
   }
   closedir(dir);
   sort_list(files, flags);
   if (header)
   {
      if (*printed)
         ft_printf("\n");
      ft_printf("%s:\n", path);
   }
   *printed = 1;
   printfiles(files, flags[FLAG_L]);
   if (flags[FLAG_R_BIG])
      recurse_subdirs(path, files, flags, printed);
   ft_lstclear(&files, free_file);
}

void lister(t_list *targets, int *flags)
{
   t_list *tmp = targets;
   t_list *files = NULL;
   t_list *dirs = NULL;
   struct stat info;
   int printed = 0;

   while (tmp)
   {
      t_file *f = malloc(sizeof(t_file));
      if (lstat((char *)tmp->content, &info) != -1)
      {
         fill_file(f, ft_strdup(tmp->content), &info);
         if (S_ISDIR(f->mode))
            ft_lstadd_back(&dirs, ft_lstnew(f));
         else
            ft_lstadd_back(&files, ft_lstnew(f));
      }
      else
      {
         ft_printf("an error occured\n");
         free(f);
      }
      tmp = tmp->next;
   }
   sort_list(files, flags);
   sort_list(dirs, flags);
   if (files)
   {
      printfiles(files, flags[FLAG_L]);
      printed = 1;
   }
   tmp = dirs;
   while (tmp)
   {
      t_file *file = tmp->content;
      list_dir(file->file_name, flags, files || ft_lstsize(dirs) > 1, &printed);
      tmp = tmp->next;
   }
   ft_lstclear(&files, free_file);
   ft_lstclear(&dirs, free_file);
}
