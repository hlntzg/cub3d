/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:16:18 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/17 14:13:15 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	position_size(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map_size.x < j)
				data->map_size.x = j;
			j++;
		}
		i++;
	}
	data->map_size.y = i;
}

static int	fill(t_data *data, t_coord size, int row, int col)
{
	if (row < 0 || col < 0 || row >= size.y || col >= size.x)
	{
		ft_putstr_fd("Error\nMap is not enclosed by walls!\n", 2);
		return (EXIT_FAILURE);
	}
	if (data->map_access[row][col] == '1')
		return (0);
	if (data->map_access[row][col] == ' ' || data->map_access[row][col] == '\t')
	{
		ft_putstr_fd("Error\nMap is not enclosed by walls!\n", 2);
		return (EXIT_FAILURE);
	}
	data->map_access[row][col] = '1';
	if (fill(data, size, row - 1, col) ||
		fill(data, size, row + 1, col) ||
		fill(data, size, row, col - 1) ||
		fill(data, size, row, col + 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_accessible(t_data *data)
{
	int		i;
	int		error;

	i = 0;
	position_size(data);
	data->map_access = ft_calloc(data->map_size.y + 1, sizeof(char *));
	if (!data->map_access)
		return (ft_putstr_fd("Error\nMemory allocation failed!\n", 2), 1);
	while (i < data->map_size.y)
	{
		data->map_access[i] = ft_strdup(data->map[i]);
		if (!data->map_access[i])
		{
			free_char_array(data->map_access);
			return (ft_putstr_fd("Error\nMemory allocation failed!\n", 2), 1);
		}
		i++;
	}
	error = fill(data, data->map_size, data->player_start.y, data->player_start.x);
	free_char_array(data->map_access);
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
