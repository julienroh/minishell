/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/01/24 18:18:12 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_expand(t_env *env, t_part *part, int *i_dollar)
{
	int		i;
	char	*check;

	i = 0;
	(*i_dollar)++;
	check = malloc(sizeof(char) * (ft_strlen(part->value + *i_dollar) + 1));
	if (!check)
		return (NULL);
	while (part->value[*i_dollar] && (ft_isalnum(part->value[*i_dollar])
			|| part->value[*i_dollar] == '_'))
		check[i++] = part->value[(*i_dollar)++];
	check[i] = '\0';
	i = -1;
	while (env[++i].id)
	{
		if (ft_strncmp(env[i].id, check, ft_strlen(check)) == 0
			&& ft_strlen(check) == ft_strlen(env[i].id))
		{
			free(check);
			return (env[i].value);
		}
		i++;
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

static void	parts_expand(t_token *token, t_env *env)
{
	t_part	*p;

	p = token->parts;
	while (p)
	{
		if (p->expand == 1)
			expand_part(p, env);
		p = p->next;
	}
}

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

char	**lexer_expand_to_args(t_lexer *lexer, t_env *env)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (lexer->token_total + 1));
	if (!args)
		return (NULL);
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
