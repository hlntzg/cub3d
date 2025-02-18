/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:20:47 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/18 12:58:52 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_data(t_data *data)
{
	data->no = ft_calloc(256, sizeof(char));
	if (!data->no)
		return (ft_putstr_fd("Error : calloc failed for NO", 2), 1);
	data->so = ft_calloc(256, sizeof(char));
	if (!data->so)
		return (ft_putstr_fd("Error : calloc failed for SO", 2), 1);
	data->we = ft_calloc(256, sizeof(char));
	if (!data->we)
		return (ft_putstr_fd("Error : calloc failed for WE", 2), 1);
	data->ea = ft_calloc(256, sizeof(char));
	if (!data->ea)
		return (ft_putstr_fd("Error : calloc failed for EA", 2), 1);
	data->map = NULL;
	data->floor = 0;
	data->ceiling = 0;
	data->lines = 0;
	data->columns = 0;
	data->player_pos.x = 0;
	data->player_pos.y = 0;
	return (0);
}

int	init_game(t_game *game)
{
	game->data = ft_calloc(1, sizeof(t_data));
	if (!game->data)
		return (ft_putstr_fd("Error : calloc failed for game->data", 2), 1);
	if (init_data(game->data) == 1)
		return (EXIT_FAILURE);
	game->txtr = ft_calloc(1, sizeof(t_txtr));
	if (!game->txtr)
		return (ft_putstr_fd("Error : calloc failed for game->txtr", 2), 1);
	/*game->img = ft_calloc(1, sizeof(t_img));
	if (!game->img)
		return (ft_putstr_fd("Error : calloc failed for game->img", 2), 1);*/
	return (EXIT_SUCCESS);
}
