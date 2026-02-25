#include "ft_ls.h"

void print_list(t_list *head)
{
   t_list *tmp = head;
   while (tmp)
   {
      ft_printf("%s ",(char *) tmp->content);
      tmp = tmp->next;
   }
}

int updateFlagsArray(int *flags, char c)
{
   if (c == 'a')
      flags[FLAG_A] = 1;
   else if (c == 'l')
      flags[FLAG_L] = 1;
   else if (c == 'r')
      flags[FLAG_R] = 1;
   else if (c == 't')
      flags[FLAG_T] = 1;
   else if (c == 'R')
      flags[FLAG_R_BIG] = 1;
   else
      return 0;
   return 1;
}

int parseFlag(char *s, int *flags)
{
   if (ft_strlen(s) == 2)
      return updateFlagsArray(flags, s[1]);
   int i = 1;
   while (s[i])
   {
      int success = updateFlagsArray(flags, s[i]);
      if (!success)
         return 0;
      i++;
   }
   return 1;
}

int startsWithHiphen(char *s)
{
   if (!s)
      return 0;
   if (s[0] == '-')
      return 1;
   return 0;
}


