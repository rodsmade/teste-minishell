/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:20:55 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/12 23:31:31 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	jump_whitespaces(char* string)
{
	int	i;

	i = -1;
	while (string [++i] && (string[i] == ' ' || string[i] == 't'))
		continue ;
	return (i - 1);
}

static t_list	*create_sublist(char *string)
{
	t_list	*sublist;
	char	*token_content;
	int		i;

	sublist = NULL;
	token_content = NULL;
	i = -1;
	while (string[++i])
	{
		if (string[i] && (string[i] != ' ' && string[i] != '\t'))
			token_content = ft_append_char(token_content, string[i]);
		else if (string[i] == ' ' || string[i] == '\t')
		{
			if (token_content)
				ft_lst_add_back(&sublist, ft_lst_new((void *) token_content));
			token_content = NULL;
			i += jump_whitespaces(&string[i]);
		}
	}
	if (token_content)
		ft_lst_add_back(&sublist, ft_lst_new((void *) token_content));
	return (sublist);
}

void	substitute_token_by_sublist(char *expanded_str, t_list **token_address)
{
	t_list	*new_token_sublist;

	new_token_sublist = create_sublist(expanded_str);
	// dprintf(2, "new token sublist: ");
	print_token_lst(new_token_sublist);
	if (*token_address)
	{
		ft_lst_last(new_token_sublist)->next = (*token_address)->next;
		ft_free_ptr((void *)&((*token_address)->content));
	}
	ft_free_ptr((void *)token_address);
	*token_address = new_token_sublist;
}
