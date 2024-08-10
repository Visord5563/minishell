/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:28 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/10 09:36:33 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_syntax(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0 && ft_isalpha(str[i]) == 0)
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(str, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            g_flags.exit_stat = 1;
            return;
        }
        i++;
    }
}

void ft_unset(t_env **env, char *name) 
{
    if (env == NULL || *env == NULL || name == NULL) {
        return;
    }

    t_env *current = *env;
    t_env *previous = NULL;

    while (current != NULL) 
    {
        check_syntax(name);
        if (strcmp(current->key, name) == 0) 
        {
            if (previous == NULL) { 
                *env = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

