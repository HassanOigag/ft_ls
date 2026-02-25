#include "libft/libft.h"

typedef enum e_flag{
   FLAG_L,
   FLAG_A,
   FLAG_R,
   FLAG_T,
   FLAG_R_BIG,
} t_flat;


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

//int selectedFlags = [5];


int main(int argc, char* argv[])
{
   int i = 1;
   int foundArg = 0;
   t_list *targets = NULL;
   int flagsSelected[5] = {0,0,0,0,0};
   (void) argc;

   while (argv[i])
   {
      if (!startsWithHiphen(argv[i]))
         foundArg = 1;
      if (startsWithHiphen(argv[i]) && !foundArg)
      {
         int success = parseFlag(argv[i], flagsSelected);
         if (!success)
         {
            ft_printf("not supported flag\n");
            return 0;
         }
      }
      else 
      {
         t_list *arg = ft_lstnew(ft_strdup(argv[i]));
         ft_lstadd_back(&targets, arg);
      }
      i++;
   }
   print_list(targets);
   int j = 0;
   while (j < 5)
   {
      ft_printf("%d ", flagsSelected[j]);
      j++;
   }
   return 0;
}
