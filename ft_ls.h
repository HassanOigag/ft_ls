#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef enum e_flag
{
   FLAG_L,
   FLAG_A,
   FLAG_R,
   FLAG_T,
   FLAG_R_BIG,
   FLAG_COUNT,
} t_flag;

typedef struct s_file{
   char *file_name;
   off_t size;
   mode_t mode;
   nlink_t nlink;
   uid_t uid;
   gid_t gid;
   time_t mtime;
   blkcnt_t blocks;
} t_file;



int starts_with_hyphen(char *s);
void print_list(t_list *head);
int parse_flag(char *s, int *flags);
int update_flags_array(int *flags, char c);
int is_flag_stopper(char *s);
void print_parser_result(t_list *targets, int *flags);
t_list *parser(char **argv, int *flags_selected);

#endif
