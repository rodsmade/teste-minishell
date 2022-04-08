/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:21:28 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/08 00:27:07 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_command_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_free_ptr((void *)&lst);
		lst = tmp;
	}
}

void	free_t_command(t_command *cmd)
{
	free_t_command_list(cmd->cmds_with_flags);
	free_t_command_list(cmd->inputs);
	free_t_command_list(cmd->outputs);
	free_t_command_list(cmd->heredocs);
	free_t_command_list(cmd->o_concats);
	free_t_command_list(cmd->err);
	return ;
}

void	free_main_pipeline(void)
{
	t_list	*lst;
	t_list	*tmp;

	lst = g_tudao.command_table.main_pipeline;
	while (lst)
	{
		free_t_command((t_command *)lst->content);
		tmp = lst->next;
		ft_free_ptr((void *)&(lst->content));
		ft_free_ptr((void *)&(lst));
		lst = tmp;
	}
}

void	close_and_free_pipes(void)
{
	int	i;

	if (!g_tudao.cmd_pipes)
		return ;
	i = -1;
	while (++i < ft_lst_size(g_tudao.command_table.main_pipeline) - 1)
	{
		close(g_tudao.cmd_pipes[i][0]);
		close(g_tudao.cmd_pipes[i][1]);
		free(g_tudao.cmd_pipes[i]);
	}
	free(g_tudao.cmd_pipes);
	return ;
}

void	free_and_exit_fork(char *err_msg)
/**
 * TODO: handle properly the return code.
 */
{
	if (err_msg)
	{
		ft_putendl_fd(err_msg, 2);
		ft_free_ptr((void *)&err_msg);
	}
	close_and_free_pipes();
	free_g_tudao();
	exit(1);
	return ;
}
