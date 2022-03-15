/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/14 22:59:07 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *line_read, int *index)
{
	char	quote_type;

	if (line_read[(*index)] == 39 || line_read[(*index)] == 34)
	{
		quote_type = line_read[(*index)];
		*index = (*index) + 1;
		while (line_read[(*index)] && line_read[(*index)] != quote_type)
			*index = (*index) + 1;
	}
}

void	quoted_generate(char *line_read, int *index, char *content)
{
	char	quote_type;
	
	if (line_read[(*index)] == 39 || line_read[(*index)] == 34)
	{
		quote_type = line_read[(*index)];
		content[(*index)] = line_read[(*index)];
		*index = (*index) + 1;
		while (line_read[(*index)] && line_read[(*index)] != quote_type)
		{
			content[(*index)] = line_read[(*index)];
			*index = (*index) + 1;
		}
	}
}

int	count_redirect(char *line_read)
{
	int	i;

	i = 0;
	if ((line_read[i] == '>' && line_read[i + 1] && line_read[i + 1] == '>') || \
		(line_read[i] == '<' && line_read[i + 1] && line_read[i + 1] == '<') || \
		(line_read[i] == '&' && line_read[i + 1] && line_read[i + 1] == '&') || \
		(line_read[i] == '|' && line_read[i + 1] && line_read[i + 1] == '|'))
		return (2);
	else if (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '&' || line_read[i] == '|')
		return (1);
	else
		return (0);
}

void	redirect_gen(char *line_read, char *content)
{
	int	i;

	i = 0;
	if ((line_read[i] == '>' && line_read[i + 1] && line_read[i + 1] == '>') || \
		(line_read[i] == '<' && line_read[i + 1] && line_read[i + 1] == '<') || \
		(line_read[i] == '&' && line_read[i + 1] && line_read[i + 1] == '&') || \
		(line_read[i] == '|' && line_read[i + 1] && line_read[i + 1] == '|'))
	{
		content[i] = line_read[i];
		content[i + 1] = line_read[i + 1];
		content[i + 2] = '\0';
	}
	else if (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '&' || line_read[i] == '|')
	{
		content[i] = line_read[i];
		content[i + 1] = '\0';
	}
}

int	token_len(char *line_read)
{
	int		i;
	int		redirect;

	i = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			skip_quotes(line_read, &i);
			if (line_read[i])
			{
				i++;
				redirect = count_redirect(&line_read[i]);
			}
		}
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

	g_tudao.token_list = NULL;
	i = 0;
	len = 0;
	while (line_read[i])
	{
		while (line_read[i] && (line_read[i] == ' ' || line_read[i] == '\t'))
			i++;
		len = token_len(&line_read[i]);
		if (len)
		{
			content = (char *)malloc(sizeof(char) * (len + 1));
			tokenizer(&line_read[i], content);
			ft_lstadd_back(&g_tudao.token_list, ft_lstnew(content));
			content = NULL;
		}
		i += len;
	}
	for (t_list	*pivot = g_tudao.token_list; pivot != NULL; pivot = pivot->next)
	{
		printf("{%s}", (char *)pivot->content);
	}
	printf("\n");
}

