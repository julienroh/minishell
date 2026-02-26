/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/02/26 14:00:08 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The only acceptable char for the id of a value are ft_isalnum == 1 and "_".
So first, the function increase "i_dollar" until we found a forbidden char for
the id of a value. Then we take this potential id and check if there is the same
id in our env struct. If the answer is yes, we change the value after the "$" by
the value in the struct.
*/

static char	*check_expand(t_env *env, t_part *part, int *i_dollar)
{
	int		i;
	char	*check;
	t_env	*current;

	i = 0;
	(*i_dollar)++;
	current = env;
	check = malloc(sizeof(char) * (ft_strlen(part->value + *i_dollar) + 1));
	if (!check)
	{
		
	}
	while (part->value[*i_dollar] && (ft_isalnum(part->value[*i_dollar])
			|| part->value[*i_dollar] == '_'))
		check[i++] = part->value[(*i_dollar)++];
	check[i] = '\0';
	while (current != NULL)
	{
		if (ft_strncmp(current->id, check, ft_strlen(check)) == 0
			&& ft_strlen(check) == ft_strlen(current->id))
			return (free(check), current->value);
		current = current->next;
	}
	free(check);
	return (NULL);
}

static void	expand_part(t_part *part, t_env *env)
{
	int		i;
	char	*env_value;
	char	*old_value;

	i = 0;
	while (part->value[i])
	{
		if (part->value[i] == '$')
		{
			env_value = check_expand(env, part, &i);
			if (env_value != NULL)
			{
				old_value = part->value;
				part->value = env_value;
				free(old_value);
			}
		}
		else
			i++;
	}
}

/*Expand the token part if needed.
*/

static void	parts_expand(t_token *token, t_env *env)
{
	t_part	*p;

	p = token->parts;
	while (p)
	{
		printf("p->expand = : %d\n", p->expand);
		if (p->expand == 1)
			expand_part(p, env);
		p = p->next;
	}
}

/*Make ft_strjoin on all parts of the token to have only one string.
*/

static char	*join_parts(t_token token)
{
	char	*to_return;
	char	*tmp;
	t_part	*p;

	to_return = ft_strdup("");
	p = token.parts;
	while (p)
	{
		tmp = ft_strjoin(to_return, p->value);
		free(to_return);
		to_return = tmp;
		p = p->next;
	}
	return (to_return);
}

/*Fontion that converts the struct lexer into a (char *) array. We detect if a
value needs to be expand by searching for the char "$"*/

char	**lexer_expand_to_args(t_lexer *lexer, t_env *env)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (lexer->token_total + 1));
	if (!args)
	{
		
	}
	while (i < lexer->token_total)
	{
		parts_expand(&lexer->tokens[i], env);
		args[i] = join_parts(lexer->tokens[i]);
		i++;
	}
	args[i] = NULL;
	i = 0;
	while (args[i])
		printf("args = : %s\n", args[i++]);
	return (args);
}
