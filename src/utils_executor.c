/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:03 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/18 14:38:34 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**assemble_cmd_array(t_command *command)
{
	char	**cmd_arr;
	t_list	*pivot;
	int		lst_len;
	int		i;

	lst_len = ft_lst_size(command->cmds_with_flags);
	cmd_arr = (char **)malloc((lst_len + 1) * sizeof(char *));
	pivot = command->cmds_with_flags;
	i = 0;
	while (pivot)
	{
		cmd_arr[i] = (char *)pivot->content;
		i++;
		pivot = pivot->next;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

char	*find_cmd_in_path_var(char *command_str)
{
	char	*all_paths;
	char	**split_paths;
	char	*cmd_path;
	int		i;

	if (command_str && command_str[0] != '\0')
	{
		all_paths = read_hashtable(g_tudao.hashtable[hash_string("PATH")],
				"PATH");
		split_paths = ft_split(all_paths, ':');
		i = -1;
		while (split_paths[++i])
		{
			cmd_path = ft_strjoin_3(split_paths[i], "/", command_str);
			if (access(cmd_path, F_OK) == 0)
			{
				ft_free_arr((void *)&split_paths);
				return (cmd_path);
			}
			else
				ft_free_ptr((void *)&cmd_path);
		}
		ft_free_arr((void *)&split_paths);
	}
	return (NULL);
}

char	*find_cmd_path(char *command_str)
{
	if (has_absolute_path(command_str))
	{
		if (access(command_str, F_OK) == 0)
		{
			if (access(command_str, X_OK) == 0)
			{
				g_tudao.ext_routine.msg = ft_strjoin_3("bash: ", command_str, \
				": Is a directory");
				return (command_str);
			}
			else
			{
				g_tudao.ext_routine.msg = ft_strjoin_3("bash: ", command_str, \
				": Permission denied");
				return (command_str);
			}
		}
		else
			return (NULL);
	}
	return (find_cmd_in_path_var(command_str));
}
