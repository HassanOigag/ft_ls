#ifndef FT_LS_H
#define FT_LS_H

#include "libft/libft.h"

typedef enum e_flag
{
   FLAG_L,
   FLAG_A,
   FLAG_R,
   FLAG_T,
   FLAG_R_BIG,
} t_flat;

int startsWithHiphen(char *s);
void print_list(t_list *head);
int parseFlag(char *s, int *flags);
int updateFlagsArray(int *flags, char c);

#endif
