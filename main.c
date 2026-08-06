
#include "ft_ls.h"





char *owner_name(uid_t uid)
{
   struct passwd *pw = getpwuid(uid);
   if (pw)
      return pw->pw_name;
   return "?";
}

char *group_name(gid_t gid)
{
   struct group *gr = getgrgid(gid);
   if (gr)
      return gr->gr_name;
   return "?";
}

int num_width(long n)
{
   int w = 1;
   while (n >= 10)
   {
      n /= 10;
      w++;
   }
   return w;
}

void print_pad(int n)
{
   while (n-- > 0)
      ft_printf(" ");
}

void get_widths(t_list *files, int *wl, int *wo, int *wg, int *ws)
{
   *wl = 0;
   *wo = 0;
   *wg = 0;
   *ws = 0;
   while (files)
   {
      t_file *f = files->content;
      int l = num_width(f->nlink);
      int o = ft_strlen(owner_name(f->uid));
      int g = ft_strlen(group_name(f->gid));
      int s = num_width(f->size);
      if (l > *wl) *wl = l;
      if (o > *wo) *wo = o;
      if (g > *wg) *wg = g;
      if (s > *ws) *ws = s;
      files = files->next;
   }
}

void printfiles(t_list *targets, int extended_print)
{
   t_list *tmp = targets;
   int wl, wo, wg, ws;

   get_widths(targets, &wl, &wo, &wg, &ws);
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
         print_pad(wl - num_width(file->nlink));
         ft_printf("%d", file->nlink);
         ft_printf(" ");
         char *ow = owner_name(file->uid);
         ft_printf("%s", ow);
         print_pad(wo - ft_strlen(ow));
         ft_printf("  ");
         char *gr = group_name(file->gid);
         ft_printf("%s", gr);
         print_pad(wg - ft_strlen(gr));
         ft_printf("  ");
         print_pad(ws - num_width(file->size));
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

char *build_path(char *dir, char *name)
{
   char *tmp = ft_strjoin(dir, "/");
   char *full = ft_strjoin(tmp, name);
   free(tmp);
   return full;
}

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
      free(full);
   }
   closedir(dir);
   printfiles(files, flags[FLAG_L]);
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

   printfiles(files, flags[FLAG_L]);
   t_list *tmp2 = dirs;
   while (tmp2)
   {
      t_file *file = (t_file *)tmp2->content;
      list_dir(file->file_name, flags);

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
   lister(targets, flags_selected);
   ft_lstclear(&targets, free);
   return 0;
}
