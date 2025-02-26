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
	player->p.x = 0.66;
	player->p.y = 0;
}

static void	set_southern_view(t_player *player)
{
	player->d.x = 0;
	player->d.y = 1;
	player->p.x = -0.66;
	player->p.y = 0;
}

static void	set_eastern_view(t_player *player)
{
	player->d.x = 1;
	player->d.y = 0;
	player->p.x = 0;
	player->p.y = 0.66;
}

static void	set_western_view(t_player *player)
{
	player->d.x = -1;
	player->d.y = 0;
	player->p.x = 0;
	player->p.y = -0.66;
}

void	set_player(t_game *game, t_player *player)
{
	player->position.x = game->data->player_pos.x + 0.5;
	//printf("player x: %f\n", player->position.x);
	player->position.y = game->data->player_pos.y + 0.5;
	//printf("player y: %f\n", player->position.y);
	if (game->data->dir_player == 'N')
		player->view = NORTH;
	if (game->data->dir_player == 'S')
		player->view = SOUTH;
	if (game->data->dir_player == 'E')
		player->view = EAST;
	if (game->data->dir_player == 'W')
		player->view = WEST;

	if (player->view == NORTH)
		set_northen_view(player);
	else if (player->view == SOUTH)
		set_southern_view(player);
	else if (player->view == EAST)
		set_eastern_view(player);
	else if (player->view == WEST)
		set_western_view(player);

	//printf("player->d.x = %f\n", player->d.x);
	//printf("player->d.y = %f\n", player->d.y);
	//printf("player->p.x = %f\n", player->p.x);
	//printf("player->p.y = %f\n", player->p.y);
}
