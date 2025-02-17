/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:11:53 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/17 12:53:08 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	validate_extension(char *name, char a, char b, char c)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 5)
		return (EXIT_FAILURE);
	if (len > 5 && (name[len - 5] == ' ' || name[len - 5] == '/'))
		return (EXIT_FAILURE);
	if (name[len - 4] == '.' && name[len - 3] == a && name[len - 2] == b
		&& name[len - 1] == c)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	validate_cub(char *map_name, t_game *game)
{
	char	**cub_content;
	int		exit;

	exit = 0;
	if (validate_extension(map_name, 'c', 'u', 'b') == 1)
		return (ft_putstr_fd("Error\nWrong map file. Usage: *.cub\n", 2), 1);
	cub_content = read_map(map_name);
	if (cub_content == NULL)
		return (EXIT_FAILURE);
	exit += validate_texture(cub_content, game);
	exit += validate_rgb(cub_content, game);
	if (exit != 0)
		return (EXIT_FAILURE);
	exit += read_copy_map(cub_content, game->data);
	if (exit != 0)
		return (EXIT_FAILURE);
	exit += valid_chars(game->data);
	exit += is_accessible(game->data);
	if (exit != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
