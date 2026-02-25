/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:11:40 by haoky             #+#    #+#             */
/*   Updated: 2026/02/25 14:41:17 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//SI ON FAIT VAR=2 CA LE STOCKE DANS ENV MAIS JE DOIS RAJOUTER
//UNE CONDITION QUI DIT QUE JE DOIS PAS L"AFFICHER. MAIS SI JE FAIS EXPORT SANS RIEN ALORS IL PASSE EN "AFFICHABLE"

#include "minishell.h"

static void	check_if_exist(t_env *env, char *arg)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, arg, ft_strlen(arg))
			&& (ft_strlen(tmp->id) == ft_strlen(arg)))
			tmp->printable = 1;
		tmp = tmp->next;
	}
}

/*Check if the id already exist, if that's the case, we only replace the old
value by the new one. If not, we create a new space for the new id and value.
*/

void	exec_export(char **args, t_env *env)
{
	int		i;
	char	*id;
	char	*value;
	t_env	*new;

	i = 0;

	if (!args[1])
		only_export(env);
	while (args[i + 1])
	{
		if (ft_strchr(args[i + 1], '=') == NULL)
		{
			check_if_exist(env, args[i + 1]);
			i++;
			continue ;
		}
		id = get_identifier(args[i + 1]);
		value = get_value(args[i + 1]);
		if (!check_identifier(id))
			invalid_export(id, value, args[i + 1]);
		else if (check_identifier(id) == 2)
		{
			plus_equal_condition(env, args[i + 1], 1);

		}
		else if (!already_in_struct(env, id, value, 0))
		{
			new = env_new(args[i + 1]);
			new->printable = 1;
			env_add_back(&env, new);
		}
		i++;
	}
}

//SI ON FAIT VAR=42 et ensuite export VAR, ca doit marcher
