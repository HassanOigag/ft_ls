#include "ft_ls.h"

char	*owner_name(uid_t uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	if (pw)
		return (pw->pw_name);
	return ("?");
}

char	*group_name(gid_t gid)
{
	struct group	*gr;

	gr = getgrgid(gid);
	if (gr)
		return (gr->gr_name);
	return ("?");
}

int	num_width(long n)
{
	int	w;

	w = 1;
	while (n >= 10)
	{
		n /= 10;
		w++;
	}
	return (w);
}

void	print_pad(int n)
{
	while (n-- > 0)
		ft_printf(" ");
}
