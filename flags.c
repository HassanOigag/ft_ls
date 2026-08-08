#include "ft_ls.h"

int	update_flags_array(int *flags, char c)
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
		return (-(int)c);
	return (1);
}

int	parse_flag(char *s, int *flags)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (update_flags_array(flags, s[i]) < 0)
			return (-(int)s[i]);
		i++;
	}
	return (1);
}

int	starts_with_hyphen(char *s)
{
	if (!s)
		return (0);
	if (s[1] && s[0] == '-')
		return (1);
	return (0);
}

int	is_flag_stopper(char *s)
{
	if (ft_strlen(s) == 2 && s[0] == '-' && s[1] == '-')
		return (1);
	return (0);
}
