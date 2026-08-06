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

void print_perms(t_file *file)
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
}

void print_long(t_file *file, int wl, int wo, int wg, int ws)
{
   print_perms(file);
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

void printfiles(t_list *targets, int extended_print)
{
   t_list *tmp = targets;
   int wl, wo, wg, ws;

   get_widths(targets, &wl, &wo, &wg, &ws);
   while (tmp)
   {
      t_file *file = (t_file *) tmp->content;

      if (extended_print)
         print_long(file, wl, wo, wg, ws);
      else
         ft_printf("%s\n", file->file_name);
      tmp = tmp->next;
   }
}
