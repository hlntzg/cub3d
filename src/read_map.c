/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:46:22 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/14 15:57:34 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	*read_file_content(int fd)
{
	char	*file_content;
	char	*line;
	char	*tmp_content;

	file_content = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp_content = file_content;
		file_content = ft_strjoin(tmp_content, line);
		free(line);
		free(tmp_content);
		line = get_next_line(fd);
	}
	return (file_content);
}

char	**read_map(char *path)
{
	int		fd;
	char	*file_content;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nNo such file or directory\n", 2);
		return (NULL);
	}
	file_content = read_file_content(fd);
	close(fd);
	if (ft_strlen(file_content) == 0)
	{
		free(file_content);
		ft_putstr_fd("Error\nFile is empty.\n", 2);
		return (NULL);
	}
	map = ft_split(file_content, '\n');
	free(file_content);
	return (map);
}
