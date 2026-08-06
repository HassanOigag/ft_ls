#include "ft_ls.h"

void list_dir(char *path, int *flags)
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
      if (entry->d_name[0] == '.')
         continue;

      t_file *f = malloc(sizeof(t_file));
      char *full = build_path(path, entry->d_name);
      if (lstat(full, &info) != -1)
      {
         fill_file(f, ft_strdup(entry->d_name), &info);
         ft_lstadd_back(&files, ft_lstnew(f));
      }
      else
      {
         ft_printf("an error occured\n");
         free(f);
      }
      free(full);
   }
   closedir(dir);
   printfiles(files, flags[FLAG_L]);
   ft_lstclear(&files, free_file);
}

void lister(t_list *targets, int *flags)
{
   t_list *tmp = targets;
   t_list *files = NULL;
   t_list *dirs = NULL;
   struct stat info;

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
   printfiles(files, flags[FLAG_L]);
   ft_lstclear(&files, free_file);
   tmp = dirs;
   while (tmp)
   {
      t_file *file = (t_file *)tmp->content;
      list_dir(file->file_name, flags);
      tmp = tmp->next;
   }
   ft_lstclear(&dirs, free_file);
}
