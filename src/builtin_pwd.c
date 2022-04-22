/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:22:34 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/22 19:07:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*buffer;
	char	*curr_path;

	buffer = NULL;
	curr_path = getcwd(buffer, 0);
	if (!curr_path)
	{
		g_tudao.exit.code = EXIT_FAILURE;
		g_tudao.exit.msg = \
			ft_strdup("builtin_pwd: Couldn't find current path");
	}
	else
	{
		g_tudao.exit.code = 0;
		ft_putendl_fd(curr_path, 1);
	}
	ft_free_ptr((void *)&curr_path);
	return ;
}
