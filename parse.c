/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:56:10 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 17:56:12 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	handle_flags(char *arg, int *flags)
{
	int	success;

	success = parse_flag(arg, flags);
	if (success < 0)
	{
		ft_putstr_fd("ft_ls: invalid option -- ", 2);
		ft_putchar_fd(-success, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

int	parse_arg(char *arg, int *flags, int *found, t_list **targets)
{
	if (is_flag_stopper(arg))
		*found = 1;
	else if (starts_with_hyphen(arg) && !*found)
		return (handle_flags(arg, flags));
	else
	{
		*found = 1;
		ft_lstadd_back(targets, ft_lstnew(ft_strdup(arg)));
	}
	return (1);
}

t_list	*parser(char **argv, int *flags)
{
	int		i;
	int		found;
	t_list	*targets;

	i = 1;
	found = 0;
	targets = NULL;
	while (argv[i])
	{
		if (!parse_arg(argv[i], flags, &found, &targets))
		{
			ft_lstclear(&targets, free);
			return (NULL);
		}
		i++;
	}
	if (!targets)
		ft_lstadd_back(&targets, ft_lstnew(ft_strdup(".")));
	return (targets);
}
