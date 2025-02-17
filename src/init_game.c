/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:20:47 by jmouette          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/14 15:49:02 by jmouette         ###   ########.fr       */
=======
/*   Updated: 2025/02/17 11:26:49 by jmouette         ###   ########.fr       */
>>>>>>> 50b06aa15b0e7418e861f79445118d84fa569d45
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
<<<<<<< HEAD
	data->player_start = ft_calloc(1, sizeof(t_coord));
	if (!data->player_start)
		return (ft_putstr_fd("Error : calloc failed for player start", 2), 1);
	data->player_start->x = 0;
	data->player_start->y = 0;
=======
	data->player_start.x = 0;
	data->player_start.y = 0;
>>>>>>> 50b06aa15b0e7418e861f79445118d84fa569d45
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
	game->img = ft_calloc(1, sizeof(t_img));
	if (!game->img)
		return (ft_putstr_fd("Error : calloc failed for game->img", 2), 1);
	return (EXIT_SUCCESS);
}
