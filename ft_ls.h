/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:57:06 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 17:57:08 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <string.h>

typedef enum e_flag
{
	FLAG_L,
	FLAG_A,
	FLAG_R,
	FLAG_T,
	FLAG_R_BIG,
	FLAG_COUNT,
}	t_flag;

typedef struct s_file
{
	char		*file_name;
	off_t		size;
	mode_t		mode;
	nlink_t		nlink;
	uid_t		uid;
	gid_t		gid;
	time_t		mtime;
	long		mtime_nsec;
	blkcnt_t	blocks;
	char		*link;
}	t_file;

typedef struct s_width
{
	int	nlink;
	int	owner;
	int	group;
	int	size;
}	t_width;

int		err_status(int set);

int		update_flags_array(int *flags, char c);
int		parse_flag(char *s, int *flags);
int		starts_with_hyphen(char *s);
int		is_flag_stopper(char *s);
int		handle_flags(char *arg, int *flags);
int		parse_arg(char *arg, int *flags, int *found, t_list **targets);
t_list	*parser(char **argv, int *flags);

char	*build_path(char *dir, char *name);
void	fill_file(t_file *f, char *name, struct stat *info);
void	free_file(void *content);
char	*read_link(char *path);
void	print_error(char *path);

void	lister(t_list *targets, int *flags);
void	build_targets(t_list *targets, t_list **files, t_list **dirs);
void	add_target(char *name, t_list **files, t_list **dirs);
void	list_dirs(t_list *dirs, int *flags, int header, int *printed);
void	print_header(char *path, int *printed);

void	list_dir(char *path, int *flags, int header, int *printed);
void	read_entries(DIR *dir, char *path, int *flags, t_list **files);
void	add_entry(char *path, char *name, t_list **files);
void	recurse_subdirs(char *path, t_list *files, int *flags, int *printed);
int		is_dot_dir(char *name);

void	printfiles(t_list *targets, int extended_print, int show_total);
void	print_long(t_file *file, t_width w);
void	get_widths(t_list *files, t_width *w);
long	get_total(t_list *files);

char	*owner_name(uid_t uid);
char	*group_name(gid_t gid);
int		num_width(long n);
void	print_pad(int n);

char	file_type(mode_t m);
char	spec_char(mode_t m, int xbit, int sbit);
void	print_rwx(mode_t m, int rbit, int wbit);
void	print_perms(t_file *file);

void	sort_list(t_list *list, int *flags);
void	sort_files(t_list *list, int (*cmp)(t_file *, t_file *), int rev);
void	swap_content(t_list *a, t_list *b);
int		cmp_name(t_file *a, t_file *b);
int		cmp_time(t_file *a, t_file *b);

#endif
