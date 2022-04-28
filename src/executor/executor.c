/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/26 20:40:45 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_to_execve(t_command *command)
{
	char	**cmd_arr;
	char	*cmd_path;
	char	**hashtable_arr;

	cmd_arr = assemble_cmd_array(command);
	cmd_path = find_cmd_path(cmd_arr);
	hashtable_arr = hashtable_to_array();
	if (execve(cmd_path, cmd_arr, hashtable_arr) == -1)
	{
		ft_free_ptr((void *)&cmd_path);
		ft_free_ptr((void *)&cmd_arr);
		ft_free_arr((void *)&hashtable_arr);
		free_and_exit_fork(NULL, EXIT_FAILURE);
	}
}

void	execute_built_in(t_command *command)
{
	char	*built_in_str;
	t_list	*cmd_lst;

	cmd_lst = command->cmds_with_flags;
	built_in_str = (char *) cmd_lst->content;
	if (ft_strncmp(built_in_str, "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(built_in_str, "cd", 3) == 0)
		builtin_cd(cmd_lst);
	else if (ft_strncmp(built_in_str, "echo", 5) == 0)
		builtin_echo(cmd_lst);
	else if (ft_strncmp(built_in_str, "env", 4) == 0)
		builtin_env(cmd_lst);
	else if (ft_strncmp(built_in_str, "exit", 5) == 0)
		builtin_exit(command);
	else if (ft_strncmp(built_in_str, "export", 7) == 0)
		builtin_export(cmd_lst);
	else if (ft_strncmp(built_in_str, "unset", 6) == 0)
		builtin_unset(cmd_lst);
	return ;
}

void	execute_command(t_command *cmd)
{
	if (cmd->cmds_with_flags)
	{
		if (is_built_in(cmd->cmds_with_flags->content))
		{
			execute_built_in(cmd);
			free_and_exit_fork(g_tudao.exit.msg, g_tudao.exit.code);
		}
		else
			send_to_execve(cmd);
	}
	else
		free_and_exit_fork(g_tudao.exit.msg, g_tudao.exit.code);
	return ;
}

void	capture_redirections(int cmd_counter, t_command *cmd)
{
	int	total_pipes;

	total_pipes = ft_lst_size(g_tudao.command_table.main_pipeline) - 1;
	if (!cmd->heredocs)
	{
		if (cmd_counter)
			dup2(g_tudao.cmd_pipes[cmd_counter - 1][0], STDIN_FILENO);
	}
	else
		capture_heredocs(cmd, cmd_counter);
	if (cmd_counter != total_pipes && total_pipes)
		dup2(g_tudao.cmd_pipes[cmd_counter][1], STDOUT_FILENO);
	capture_inputs(cmd);
	capture_outputs(cmd);
	capture_o_concats(cmd);
}

void	execute_pipeline(t_list *pipeline)
{
	t_list		*cmd_pivot;
	t_command	*cmd;
	int			counter;
	int			total_pipes;

	create_new_files(pipeline);
	if (pipe(g_tudao.pipe_heredoc) == -1)
		print_error_and_exit(1, ft_strdup("Error: pipe heredoc"));
	if (!execute_only_one_cmd(pipeline))
	{
		cmd_pivot = pipeline;
		cmd = (t_command *) cmd_pivot->content;
		counter = -1;
		total_pipes = ft_lst_size(pipeline) - 1;
		g_tudao.cmd_pipes = ft_make_pipes(total_pipes);
		while (cmd_pivot)
		{
			cmd = (t_command *) cmd_pivot->content;
			fork_and_execute_cmd(total_pipes, ++counter, cmd);
			close_fds(cmd);
			cmd_pivot = cmd_pivot->next;
		}
		close_and_free_cmd_pipes();
	}
}