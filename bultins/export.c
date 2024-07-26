/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:13:33 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/24 11:52:33 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int export(const char *name, const char *value) {

    if (name == NULL || value == NULL) {
        fprintf(stderr, "Invalid arguments\n");
        return -1;
    }

    if (setenv(name, value, 1) != 0) {
        perror("setenv");
        return -1;
    }

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
