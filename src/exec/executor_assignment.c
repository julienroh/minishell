/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_assignment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 12:10:41 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/01 21:25:37 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool	is_valid_var_name_start(int c)
{
	//premier char est correct.
	if ((c >= 'A' && c <= 'Z')|| (c >= 'a' && c <= 'z') || c == '_')
		return (true);
	return (false);
}

static bool	is_valid_var_name_char(int c)
{
	//suite de la var est correct.
	if (is_valid_var_name_start(c) || (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

t_assign_type get_assignment_type(char *word)
{
	//renvoie le type d'assign + Check les erreurs de nom de vars.
	int	i;

	i = 0;
	if (!word || !word[0])
		return (NONE);
	if (!is_valid_var_name_start(word[0]))
		return (NONE);
	i = 1;
	while (word[i] && is_valid_var_name_char(word[i]))
		i++;
	if (word[i] == '=')
		return (SET);
	if (word[i] == '+' && word[i+1] == '=')
		return (APPEND);
	return (NONE);
}

int	count_prefix_assignments(char **argv)
{
	//nombre de VAR=machin, VAR+=machin...
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i] && get_assignment_type(argv[i]) != NONE)
		i++;
	return (i);
}

bool	is_only_assignment_no_cmd(char **argv, int assign_count)
{
	//uniquement des assign dans mon argv, pas de vrai cmds.
	if (argv[assign_count++] == NULL)
		return (true);
	return (false);
}