/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:19:57 by david             #+#    #+#             */
/*   Updated: 2025/04/20 22:11:17 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void bubble_sort(char **tab1, char **tab2)
{
    int size1 = calculate_size(tab1);
    int size2 = calculate_size(tab2);
    int total_size = size1 + size2;

    char **temp = merge_arrays(tab1, size1, tab2, size2);
    if (!temp) return;

    sort_array(temp, total_size);
    print_and_free(temp, total_size);
}

char **allocate_and_copy_first_array(char **tab1, int size1, int total_size)
{
    char **temp = malloc((total_size + 1) * sizeof(char *));
    if (!temp)
        return NULL;

    int i = 0;
    while (i < size1)
    {
        temp[i] = ft_strdup(tab1[i]);  // Utilisation de ft_strdup au lieu de strdup
        if (!temp[i])
        {
            while (i-- > 0)
                free(temp[i]);
            free(temp);
            return NULL;
        }
        i++;
    }
    return temp;
}

int copy_second_array(char **temp, char **tab2, int size1, int size2)
{
    int i = 0;
    while (i < size2)
    {
        temp[size1 + i] = ft_strdup(tab2[i]);  // Utilisation de ft_strdup
        if (!temp[size1 + i])
        {
            while (size1 + i-- > 0)
                free(temp[size1 + i]);
            return 0;
        }
        i++;
    }
    temp[size1 + size2] = NULL;
    return 1;
}

char **merge_arrays(char **tab1, int size1, char **tab2, int size2)
{
    int total_size = size1 + size2;
    char **temp = allocate_and_copy_first_array(tab1, size1, total_size);
    if (!temp)
        return NULL;

    if (!copy_second_array(temp, tab2, size1, size2))
    {
        free(temp);
        return NULL;
    }
    return temp;
}

void sort_array(char **temp, int size)
{
    int swapped = 1;
    while (swapped)
    {
        swapped = 0;
        int i = 0;
        while (i < size - 1)
        {
            if (strncmp(temp[i], temp[i + 1], 256) > 0)
            {
                char *swap = temp[i];
                temp[i] = temp[i + 1];
                temp[i + 1] = swap;
                swapped = 1;
            }
            i++;
        }
    }
}
