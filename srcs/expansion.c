/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/02/26 15:25:24 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int expansion(t_tok *tok, t_shell *shell)
{
	char *var_value;

	var_value = ft_findvar(tok->str, shell);
	free(tok->str);
	tok->type = ft_strdup(var_value);
	free (var_value);
	var_value = NULL;
	return (1);
}

char *ft_findvar(char *var_name, t_shell *shell)
{
	char *var_line;
	char *var_value;
	int var_lenth;

	var_value = NULL;
	var_lenth = ft_strlen(var_name + 1);
	var_line = getenv(var_name + 1);
	var_value = ft_strdup(var_line + var_lenth + 1);
	return(var_value);
}
