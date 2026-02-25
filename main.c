
#include "ft_ls.h"

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
