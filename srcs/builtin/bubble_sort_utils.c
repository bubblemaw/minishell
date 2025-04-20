/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:02:06 by david             #+#    #+#             */
/*   Updated: 2025/04/20 22:13:39 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int calculate_size(char **tab)
{
    int size = 0;
    if (tab != NULL)
    {
        while (tab[size] != NULL)
            size++;
    }
    return size;
}

void print_and_free(char **temp, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("%s\n", temp[i]);
        free(temp[i]);
        i++;
    }
    free(temp);
}
