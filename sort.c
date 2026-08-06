#include "ft_ls.h"

int cmp_name(t_file *a, t_file *b)
{
   size_t la = ft_strlen(a->file_name);
   size_t lb = ft_strlen(b->file_name);
   size_t n = la > lb ? la : lb;

   return ft_strncmp(a->file_name, b->file_name, n + 1);
}

void sort_files(t_list *list, int (*cmp)(t_file *, t_file *))
{
   int swapped = 1;
   t_list *tmp;

   if (!list)
      return;
   while (swapped)
   {
      swapped = 0;
      tmp = list;
      while (tmp->next)
      {
         if (cmp(tmp->content, tmp->next->content) > 0)
         {
            void *value = tmp->content;
            tmp->content = tmp->next->content;
            tmp->next->content = value;
            swapped = 1;
         }
         tmp = tmp->next;
      }
   }
}

void sort_list(t_list *list, int *flags)
{
   (void) flags;
   sort_files(list, cmp_name);
}
