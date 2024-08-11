/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:13:33 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/10 10:16:01 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sort_env(t_env **env)
{
    t_env *tmp;
    t_env *tmp2;
    char *tmp3;

    tmp = *env;
    while (tmp)
    {
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (ft_strcmp(tmp->key, tmp2->key) > 0)
            {
                tmp3 = tmp->key;
                tmp->key = tmp2->key;
                tmp2->key = tmp3;
                tmp3 = tmp->value;
                tmp->value = tmp2->value;
                tmp2->value = tmp3;
            }
            tmp2 = tmp2->next;
            if(!tmp->value)
                printf("declare -x %s=%s\n", tmp->key, tmp->value);
            else
                printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        }
        tmp = tmp->next;
    }
}


int ft_export(char **cmd, t_env **env) 
{
    int i;       

    i = 0;
    if (!cmd[1])
    {
        sort_env(env);
        return 0;
    }
    else if ((!ft_isalpha(cmd[1][i])) && ft_isdigit(cmd[1][i]))
    {
        ft_putstr_fd("minishell: unset: `", 2);
        ft_putstr_fd(cmd[1], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        exit_status(env, "1");
        return 0;
    }
    
    return 0;
}
