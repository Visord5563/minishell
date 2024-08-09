/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:13:33 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/09 14:02:37 by ehafiane         ###   ########.fr       */
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
    (void)cmd;
    // if (!(cmd[0][1] == '_' && ft_isalpha(cmd[0][1])))
    // {
    //     printf("minishell: export: `%s': not a valid identifier\n", cmd[1]);
    // }
        sort_env(env);
        // export_env(*env, &cmd[1]);
    

    
    
    return 0;
}
