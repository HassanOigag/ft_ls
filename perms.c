/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:56:16 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 17:56:19 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	file_type(mode_t m)
{
	if (S_ISDIR(m))
		return ('d');
	if (S_ISLNK(m))
		return ('l');
	if (S_ISCHR(m))
		return ('c');
	if (S_ISBLK(m))
		return ('b');
	if (S_ISFIFO(m))
		return ('p');
	if (S_ISSOCK(m))
		return ('s');
	return ('-');
}

char	spec_char(mode_t m, int xbit, int sbit)
{
	char	base;

	base = 's';
	if (sbit == S_ISVTX)
		base = 't';
	if (m & sbit)
	{
		if (m & xbit)
			return (base);
		return (base - 32);
	}
	if (m & xbit)
		return ('x');
	return ('-');
}

void	print_rwx(mode_t m, int rbit, int wbit)
{
	if (m & rbit)
		ft_printf("r");
	else
		ft_printf("-");
	if (m & wbit)
		ft_printf("w");
	else
		ft_printf("-");
}

void	print_perms(t_file *file)
{
	mode_t	m;

	m = file->mode;
	ft_printf("%c", file_type(m));
	print_rwx(m, S_IRUSR, S_IWUSR);
	ft_printf("%c", spec_char(m, S_IXUSR, S_ISUID));
	print_rwx(m, S_IRGRP, S_IWGRP);
	ft_printf("%c", spec_char(m, S_IXGRP, S_ISGID));
	print_rwx(m, S_IROTH, S_IWOTH);
	ft_printf("%c", spec_char(m, S_IXOTH, S_ISVTX));
}
