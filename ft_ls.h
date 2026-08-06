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
   long mtime_nsec;
   blkcnt_t blocks;
} t_file;



int starts_with_hyphen(char *s);
void print_list(t_list *head);
int parse_flag(char *s, int *flags);
int update_flags_array(int *flags, char c);
int is_flag_stopper(char *s);
void print_parser_result(t_list *targets, int *flags);
t_list *parser(char **argv, int *flags_selected);

char *build_path(char *dir, char *name);
void fill_file(t_file *f, char *name, struct stat *info);
void free_file(void *content);

void printfiles(t_list *targets, int extended_print);
char *owner_name(uid_t uid);
char *group_name(gid_t gid);
int num_width(long n);
void print_pad(int n);

void lister(t_list *targets, int *flags);
void list_dir(char *path, int *flags, int header, int *printed);
void recurse_subdirs(char *path, t_list *files, int *flags, int *printed);
int is_dot_dir(char *name);

void sort_list(t_list *list, int *flags);
void sort_files(t_list *list, int (*cmp)(t_file *, t_file *), int rev);
int cmp_name(t_file *a, t_file *b);
int cmp_time(t_file *a, t_file *b);

#endif
