#include "ft_ls.h"

char *build_path(char *dir, char *name)
{
   char *tmp = ft_strjoin(dir, "/");
   char *full = ft_strjoin(tmp, name);
   free(tmp);
   return full;
}

void free_file(void *content)
{
   t_file *f = content;
   free(f->file_name);
   free(f);
}

void fill_file(t_file *f, char *name, struct stat *info)
{
   f->file_name = name;
   f->size = info->st_size;
   f->mode = info->st_mode;
   f->uid = info->st_uid;
   f->blocks = info->st_blocks;
   f->gid = info->st_gid;
   f->mtime = info->st_mtimespec.tv_sec;
   f->mtime_nsec = info->st_mtimespec.tv_nsec;
   f->nlink = info->st_nlink;
}
