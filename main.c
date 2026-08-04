
#include "ft_ls.h"





void printfiles(t_list *targets, int extended_print)
{
   t_list *tmp = targets;


   while (tmp)
   {
      t_file *file = (t_file *) tmp->content;

      if (extended_print)
      {
         ft_printf("%c", S_ISDIR(file->mode) ? 'd' : '-');
   
         ft_printf("%c", (file->mode & S_IRUSR) ? 'r' : '-');
         ft_printf("%c", (file->mode & S_IWUSR) ? 'w' : '-');
         ft_printf("%c", (file->mode & S_IXUSR) ? 'x' : '-');
   
         ft_printf("%c", (file->mode & S_IRGRP) ? 'r' : '-');
         ft_printf("%c", (file->mode & S_IWGRP) ? 'w' : '-');
         ft_printf("%c", (file->mode & S_IXGRP) ? 'x' : '-');
   
         ft_printf("%c", (file->mode & S_IROTH) ? 'r' : '-');
         ft_printf("%c", (file->mode & S_IWOTH) ? 'w' : '-');
         ft_printf("%c", (file->mode & S_IXOTH) ? 'x' : '-');
   
         ft_printf(" ");
         ft_printf("%d", file->nlink);
         ft_printf(" ");
         ft_printf("%s", getpwuid(file->uid)->pw_name);
         ft_printf("  ");
         ft_printf("%s", getgrgid(file->gid)->gr_name);
         ft_printf("  ");
         ft_printf("%ld", file->size);
         ft_printf(" ");
         char *time_str = ctime(&file->mtime);
         ft_printf("%.12s", time_str + 4);
         ft_printf(" ");
         ft_printf("%s\n", file->file_name);
      }
      else
         ft_printf("%s  ", file->file_name);
      tmp = tmp->next;
   }
}

void list_dir(char *path)
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
      if (lstat(entry->d_name, &info) != -1)
      {
         f->file_name = ft_strdup(entry->d_name);
         f->size = info.st_size;
         f->mode = info.st_mode;
         f->uid = info.st_uid;
         f->blocks = info.st_blocks;
         f->gid = info.st_gid;
         f->mtime = info.st_mtimespec.tv_sec;
         f->nlink = info.st_nlink;
         t_list *new = ft_lstnew(f);
         ft_lstadd_back(&files, new);
      }
      else
      {
         ft_printf("an error occured\n");
         free(f);
      }
   }
   closedir(dir);
   printfiles(files, 0);
}

void lister(t_list *targets)
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
         f->file_name = tmp->content;
         f->size = info.st_size;
         f->mode = info.st_mode;
         f->uid = info.st_uid;
         f->blocks = info.st_blocks;
         f->gid = info.st_gid;
         f->mtime = info.st_mtimespec.tv_sec;
         f->nlink = info.st_nlink;
         t_list *new = ft_lstnew(f);
         if (S_ISDIR(f->mode))
            ft_lstadd_back(&dirs, new);
         else
            ft_lstadd_back(&files, new);
      }
      else
      {
         ft_printf("an error occured\n");
         free(f);
      }

      tmp = tmp->next;
   }

   printfiles(files, 0);
   t_list *tmp2 = dirs;
   while (tmp2)
   {
      t_file *file = (t_file *)tmp2->content;
      ft_printf("director int hand : %s\n", file->file_name);
      list_dir(file->file_name);

      tmp2 = tmp2->next;
   }
}

int main(int argc, char *argv[])
{

   t_list *targets = NULL;
   int flags_selected[FLAG_COUNT];
   ft_bzero(flags_selected, FLAG_COUNT * sizeof(int));
   (void) argc;

   targets = parser(argv, flags_selected);
   if (!targets) return 1;
   // print_parser_result(targets, flags_selected);
   lister(targets);
   ft_lstclear(&targets, free);
   return 0;
}
