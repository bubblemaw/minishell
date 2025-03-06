/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:01 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:08:01 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_strings(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

int	ft_found_sub(const char *s, char c, int *i)
{
	int	start;
	int	size;

	start = *i;
	while (s[*i] != '\0' && s[*i] != c)
	{
		(*i)++;
	}
	size = *i - start;
	return (size);
}

char	*ft_creat_sub(const char *s, int start, int size)
{
	char	*new_sub;
	int		j;

	new_sub = (char *)malloc(sizeof(char) * (size + 1));
	if (new_sub == NULL)
		return (NULL);
	j = 0;
	while (j < size)
	{
		new_sub[j] = s[start + j];
		j++;
	}
	new_sub[j] = '\0';
	return (new_sub);
}

char	**split_loop(const char *s, char c, char **new)
{
	int		i;
	int		size_sub_string;
	int		index;

	i = 0;
	index = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			size_sub_string = ft_found_sub(s, c, &i);
			new[index] = ft_creat_sub(s, i - size_sub_string, size_sub_string);
			if (new[index++] == NULL)
			{
				while (index > 0)
					free(new[--index]);
				free(new);
				return (NULL);
			}
		}
	}
	new[index] = NULL;
	return (new);
}

char	**ft_split(const char *s, char c)
{
	char	**new;

	if (s == NULL || *s == '\0')
	{
		new = (char **)malloc(sizeof(char *));
		if (new == NULL)
			return (NULL);
		new[0] = NULL;
		return (new);
	}
	new = (char **)malloc(sizeof(char *) * (ft_count_strings(s, c) + 1));
	if (new == NULL)
		return (NULL);
	new = split_loop(s, c, new);
	return (new);
}

// // la fonction split permet de diviser un string en plusieurs sous string
// // mis dans un tableau en 2 dimensions un fonction d'un separateur donné
// int main (void)
// {
// 	char const s1[] = "  EKip   MMS LDO   NRM 667      petasse ";
// 	char sep = ' ';
// 	char **new = ft_split(s1, sep);
// 	int i = 0;
// 	while (new[i] != NULL)
// 	{
// 		printf("[%d] : %s\n", i + 1,  new[i]);
// 		i++;
// 	}
// 	return (0);
// }
