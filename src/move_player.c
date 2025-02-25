/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:33 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/25 15:11:07 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	move_player_forward(t_game *game)
{
	double		new_x;
	double		new_y;
	t_coordd	*p;

	p = &game->player->position;

	printf("position: %f %f\n", p->x, p->y);
	new_x = p->x + game->player->d.x * MOVE_SPEED;
	new_y = p->y + game->player->d.y * MOVE_SPEED;
	if (game->data->map[(int)new_y][(int)new_x] != '1')
	{
		p->x = new_x;
		p->y = new_y;
	}
	printf("position: %f %f\n", p->x, p->y);
}

void	move_player_backward(t_game *game)
{
	double		new_x;
	double		new_y;
	t_coordd	*p;

	p = &game->player->position;
	new_x = p->x - game->player->d.x * MOVE_SPEED;
	new_y = p->y - game->player->d.y * MOVE_SPEED;
	if (game->data->map[(int)new_y][(int)new_x] != '1')
	{
		p->x = new_x;
		p->y = new_y;
	}
	printf("position: %f %f\n", p->x, p->y);
}

void	move_player_right(t_game *game)
{
	double		new_x;
	double		new_y;
	t_coordd	*p;

	p = &game->player->position;
	new_x = p->x - game->player->d.y * MOVE_SPEED;
	new_y = p->y + game->player->d.x * MOVE_SPEED;
	if (game->data->map[(int)new_y][(int)new_x] != '1')
	{
		p->x = new_x;
		p->y = new_y;
	}
	printf("position: %f %f\n", p->x, p->y);
}

void	move_player_left(t_game *game)
{
	double		new_x;
	double		new_y;
	t_coordd	*p;

	p = &game->player->position;

	new_x = p->x + game->player->d.y * MOVE_SPEED;
	new_y = p->y - game->player->d.x * MOVE_SPEED;
	if (game->data->map[(int)new_y][(int)new_x] != '1')
	{
		p->x = new_x;
		p->y = new_y;
	}
	printf("position: %f %f\n", p->x, p->y);
}
