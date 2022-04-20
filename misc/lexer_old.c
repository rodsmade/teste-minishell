/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/18 14:34:33 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	token_len(char *line_read, int *len)
{
	int		i;
	int		len;
	int		redirect;

	i = 0;
	len = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			skip_quotes(line_read, &i, len);
			if (line_read[i])
			{
				i++;
				*len = (*len) + 1;
				redirect = count_redirect(&line_read[i]);
			}
		}
		*len = (*len) -1;
		return (i);
	}
	return (redirect);
}

void	tokenizer(char *line_read, char *content)
{
	int		i;
	int		redirect;

	i = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			quoted_generate(line_read, &i, content);
			if (line_read[i])
			{
				content[i] = line_read[i];
				i++;
				redirect = count_redirect(&line_read[i]);
			}
		}
		content[i] = '\0';
	}
	else
		redirect_gen(&line_read[i], content);
}

void	lexer_line(char *line_read)
{
	char	*content;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = 0;
	while (line_read[i])
	{
		while (line_read[i] && (line_read[i] == ' ' || line_read[i] == '\t'))
			i++;
		j = token_len(&line_read[i], &len);
		if (len)
		{
			content = (char *)malloc(sizeof(char) * (len + 1));
			tokenizer(&line_read[i], content);
			ft_lst_add_back(&g_tudao.token_list, ft_lst_new(content));
			content = NULL;
		}
		i += j;
	}
}
*/