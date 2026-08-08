#include "ft_ls.h"

int	err_status(int set)
{
	static int	status;

	if (set)
		status = 1;
	return (status);
}

int	main(int argc, char **argv)
{
	t_list	*targets;
	int		flags[FLAG_COUNT];

	(void)argc;
	ft_bzero(flags, FLAG_COUNT * sizeof(int));
	targets = parser(argv, flags);
	if (!targets)
		return (1);
	lister(targets, flags);
	ft_lstclear(&targets, free);
	return (err_status(0));
}
