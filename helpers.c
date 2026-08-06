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

int update_flags_array(int *flags, char c)
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
      return -(int)c;
   return 1;
}

int parse_flag(char *s, int *flags)
{
   int i = 1;
   while (s[i])
   {
      int success = update_flags_array(flags, s[i]);
      if (success < 0)
         return success;
      i++;
   }
   return 1;
}

int starts_with_hyphen(char *s)
{
   if (!s)
      return 0;
   
   if (s[1] && s[0] == '-')
      return 1;
   return 0;
}
int is_flag_stopper(char *s)
{
   if (ft_strlen(s) == 2 && s[0] == '-' && s[1] == '-')
      return 1;
   return 0;
}

t_list *parser(char **argv, int *flags_selected)
{
   int i = 1;
   int found_arg = 0;
   t_list *targets = NULL;
   // struct stat info;
   while (argv[i])
   {
      if (is_flag_stopper(argv[i]))
      {
         found_arg = 1;
         i++;
         continue;
      }
      if (!starts_with_hyphen(argv[i]))
         found_arg = 1;
      if (starts_with_hyphen(argv[i]) && !found_arg)
      {
         int success = parse_flag(argv[i], flags_selected);
         if (success < 0)
         {
            ft_putstr_fd("ft_ls: invalid option -- ", 2);
            ft_putchar_fd(-success, 2);
            ft_putstr_fd("\n", 2);
            ft_lstclear(&targets, free);
            return NULL;
         }
      }
      else
      {
         t_list *arg = ft_lstnew(ft_strdup(argv[i]));
         // if (stat(argv[i], &info) != -1)
         //    ft_printf("stat error\n");
         // ft_printf("sizeL: %ld\n", info.st_size);  
         ft_lstadd_back(&targets, arg);
      }
      i++;
   }
   if (!targets)
   {
      t_list *arg = ft_lstnew(ft_strdup("."));
      ft_lstadd_back(&targets, arg);
   }
   return targets;
}

void print_parser_result(t_list *targets, int *flags)
{
   ft_printf("flags:\n");
   ft_printf("    l: %d\n", flags[FLAG_L]);
   ft_printf("    a: %d\n", flags[FLAG_A]);
   ft_printf("    r: %d\n", flags[FLAG_R]);
   ft_printf("    t: %d\n", flags[FLAG_T]);
   ft_printf("    R: %d\n", flags[FLAG_R_BIG]);

   ft_printf("targets: ");
   print_list(targets);
}