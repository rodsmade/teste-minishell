/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/10 11:56:33 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	get_env_variables(char **envp)
{
	int			i;
	t_list		*hashtable[TABLE_SIZE];

	i = -1;
	init_hashtable(&hashtable);
	while (envp[++i])
	{
		insert_in_hashtable(envp[i], 1, &hashtable);
	}
	print_hashtable(&hashtable);
	free_hashtable(&hashtable);
	return ;
}

void	repl(void)
{
	char	*line_read;

	line_read = NULL;
	while (1)
	{
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		add_history(line_read);
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
		if (line_read)
			ft_free_ptr((void *)&line_read);
	}
	ft_free_ptr((void *)&line_read);
	rl_clear_history();
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	write(1, "Hello World !\n", 14);
	get_env_variables(envp);
	repl();
	close(0);
	close(1);
	close(2);
	return (0);
}