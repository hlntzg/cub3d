/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:53:34 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/17 12:53:53 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	is_map(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if ((s[i] == 'N' && s[i + 1] == 'O') || (s[i] == 'S' && s[i + 1] == 'O')
		|| (s[i] == 'E' && s[i + 1] == 'A') || (s[i] == 'W' && s[i + 1] == 'E')
		|| s[i] == 'F' || s[i] == 'C')
		return (3);
	if (!(s[i] == '0' || s[i] == '1' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W'))
		return (3);
	while (s[i])
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W')
			return (EXIT_SUCCESS);
		i++;
	}
	if (s[i] == '\0')
		return (2);
	return (EXIT_FAILURE);
}

static int	copy_map(t_data *data, char **cub_content, int map_start, int i)
{
	int	j;

	j = 0;
	if (map_start == -1)
		return (ft_putstr_fd("Error\nNo map found.\n", 2), EXIT_FAILURE);
	data->map = malloc(sizeof(char *) * (i - map_start + 1));
	if (!data->map)
		return (ft_putstr_fd("Error\nMalloc failed for map\n", 2), EXIT_FAILURE);
	while (map_start < i)
	{
		data->map[j] = ft_substr(cub_content[map_start], 0,
				ft_strlen(cub_content[map_start]));
		if (data->map[j] == NULL)
			return (EXIT_FAILURE);
		map_start++;
		j++;
	}
	data->map[j] = NULL;
	return (0);
}

int	read_copy_map(char **cub_content, t_data *data)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (cub_content[i] != NULL)
	{
		if (is_map(cub_content[i]) == 0)
		{
			map_start = i;
			while (cub_content[i] != NULL && is_map(cub_content[i]) == 0)
				i++;
			while (cub_content[i] != NULL)
			{
				if (is_map(cub_content[i]) != 2)
					return (printf("Error\nMap is not at the end.\n"), 1);
				i++;
			}
			break ;
		}
		i++;
	}
	if (copy_map(data, cub_content, map_start, i) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
