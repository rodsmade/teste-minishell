/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:01:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/15 13:19:49 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ---------------------------------------------	INCLUDES	----------------
# include <readline/readline.h>	// readline(), etc.
# include <readline/history.h>	// add_history()
# include <unistd.h>	// write(), close()
# include <stdlib.h>	// free()
# include <stdbool.h>
# include "libft.h"

// ----------------------------------------------	DEFINES		----------------
# define TABLE_SIZE	50

// ----------------------------------------------	STRUCTS		----------------
typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					is_env_var;
}				t_env_var;

typedef struct s_redirections
{
	bool	has_redirect;
	int		in;
	int		out;
	int		err;
}			t_redirections;

typedef struct s_cmd_table
{
	t_list	**main_pipeline;
	bool	has_and_operator;
	bool	has_or_operator;
	t_list	**secondary_pipeline;
}				t_cmd_table;

typedef struct s_tudao
{
	t_list			*hashtable[TABLE_SIZE];
	t_list			*token_list;
	t_cmd_table		command_table;
	t_redirections	redirections;
	int				return_code;
}				t_tudao;

// ----------------------------------------------	GLOBAL VAR	----------------
t_tudao		g_tudao;

// ----------------------------------------------	PROTOTYPES	----------------
// exit_routines.c
void	free_env_var(void *element);
void	free_hashtable(t_list *(*hashtable)[TABLE_SIZE]);

// hashtable.c
void	insert_in_hashtable(char *string, int is_env_var,
			t_list *(*hashtable)[TABLE_SIZE]);

// init_routines.c
void	init_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void	init_tudao(void);

// lexer.c
void	lexer_line(char	*line_read);

// utils_lexer.c
void	skip_quotes(char *line_read, int *index);
void	quoted_generate(char *line_read, int *index, char *content);
int		count_redirect(char *line_read);
void	redirect_gen(char *line_read, char *content);
void	free_lexer(void);

// utils_test.c
void	print_hashtable(t_list *(*hashtable)[TABLE_SIZE]);

#endif