/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:36:33 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/19 15:43:01 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// 0.5 ->>  some value based on the grid dimension.
// Represents an offset for the player's position within the grid

static void	set_northen_view(t_player *player)
{
	player->d.x = 0;
	player->d.y = -1;
	player->p.x = 0.5;
	player->p.y = 0;
}

static void	set_southern_view(t_player *player)
{
	player->d.x = 0;
	player->d.y = 1;
	player->p.x = -0.5;
	player->p.y = 0;
}

static void	set_eastern_view(t_player *player)
{
	player->d.x = 1;
	player->d.y = 0;
	player->p.x = 0;
	player->p.y = 0.5;
}

static void	set_western_view(t_player *player)
{
	player->d.x = -1;
	player->d.y = 0;
	player->p.x = 0;
	player->p.y = -0.5;
}

void	set_player(t_game *game, t_player *player)
{
	player->position.x = game->data->player_pos.x + 0.5;
	player->position.y = game->data->player_pos.y + 0.5;
	if (player->view == NORTH)
		set_northen_view(player);
	else if (player->view == SOUTH)
		set_southern_view(player);
	else if (player->view == EAST)
		set_eastern_view(player);
	else if (player->view == WEST)
		set_western_view(player);
}
