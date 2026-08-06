#include "ft_ls.h"

int main(int argc, char *argv[])
{
   t_list *targets = NULL;
   int flags_selected[FLAG_COUNT];

   ft_bzero(flags_selected, FLAG_COUNT * sizeof(int));
   (void) argc;
   targets = parser(argv, flags_selected);
   if (!targets)
      return 1;
   lister(targets, flags_selected);
   ft_lstclear(&targets, free);
   return 0;
}
