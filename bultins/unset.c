/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:28 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/11 11:52:38 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void check_syntax(char *str)
{
    int i;
    t_env *tmp;
    
    i = 0;
    if (!ft_isalpha(str[i]))
    {
        ft_putstr_fd("minishell: unset: `", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        exit_status(&tmp, "1");
        return;
    }
    while (str[i])
    {
        if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(str, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            exit_status(&tmp, "1");
            return;
        }
        i++;
    }
}


void ft_unset(t_env **env, char *name) 
{
    t_env *current = *env;
    t_env *previous = NULL;
    
    if (env == NULL || *env == NULL || name == NULL) {
        ft_putstr_fd("Invalid environment or name\n", 2);
        return;
    }
    check_syntax(name);
    while (current != NULL) 
    {
        if (strcmp(current->key, name) == 0) 
        {
            if (previous == NULL)
                *env = current->next;
            else
                previous->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

