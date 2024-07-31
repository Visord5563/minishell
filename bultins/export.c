/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:13:33 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/30 16:12:36 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_export(char **cmd, t_env **env) {

    (void)env;
    (void)cmd;
    // int i = 1;
    // int j = 0;
    // char *key = NULL;
    // char *value = NULL;
    // t_env *tmp = *env;
    
    // while (cmd[i] != NULL) {
    //     j = 0;
    //     while (cmd[i][j] != '\0' && cmd[i][j] != '=') {
    //         j++;
    //     }
    //     key = ft_substr(cmd[i], 0, j);
    //     if (cmd[i][j] == '=') {
    //         value = ft_strdup(&cmd[i][j + 1]);
    //     } else {
    //         value = ft_strdup("");
    //     }
    //     while (tmp != NULL) {
    //         if (strcmp(tmp->key, key) == 0) {
    //             free(tmp->value);
    //             tmp->value = value;
    //             break;
    //         }
    //         tmp = tmp->next;
    //     }
    //     if (tmp == NULL) {
    //         add_env(env, key, value);
    //     }
    //     free(key);
    //     i++;
    // }

    return 0;
}

// int main() {
//     if (export("VAR", "Hello World") == 0) {
//         printf("VAR=%s\n", getenv("VAR"));
//     } else {
//         printf("Failed to set environment variable\n");
//     }

//     return 0;
// }
