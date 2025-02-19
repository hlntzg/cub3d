/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:33 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/19 17:03:43 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	move_player_left(t_game *game)
{
	double		new_x;
	double		new_y;
	char		**map;
	t_coordd	*p;
	t_raycast	*ray;

	map = game->data->map;
	p = &game->player->position;
	ray = game->ray;
	new_x = p->x - ray->direction.x * MOVE_SPEED;
	new_y = p->y + ray->direction.y * MOVE_SPEED;
	if (map[(int)p->y][(int)new_x] == '0')
		p->x = new_x;
	if (map[(int)new_y][(int)p->x] == '0')
		p->y = new_y;
}

void	move_player_right(t_game *game)
{
	double		new_x;
	double		new_y;
	char		**map;
	t_coordd	*p;
	t_raycast	*ray;

	map = game->data->map;
	p = &game->player->position;
	ray = game->ray;
	new_x = p->x + ray->direction.x * MOVE_SPEED;
	new_y = p->y - ray->direction.y * MOVE_SPEED;
	if (map[(int)p->y][(int)new_x] == '0')
		p->x = new_x;
	if (map[(int)new_y][(int)p->x] == '0')
		p->y = new_y;
}

void	move_player_forward(t_game *game)
{
	double		new_x;
	double		new_y;
	char		**map;
	t_coordd	*p;
	t_raycast	*ray;

	map = game->data->map;
	p = &game->player->position;
	ray = game->ray;
	new_x = p->x + ray->direction.x * MOVE_SPEED;
	new_y = p->y + ray->direction.y * MOVE_SPEED;
	if (map[(int)p->y][(int)new_x] == '0')
		p->x = new_x;
	if (map[(int)new_y][(int)p->x] == '0')
		p->y = new_y;
}

void	move_player_backward(t_game *game)
{
	double		new_x;
	double		new_y;
	char		**map;
	t_coordd	*p;
	t_raycast	*ray;

	map = game->data->map;
	p = &game->player->position;
	ray = game->ray;
	new_x = p->x - ray->direction.x * MOVE_SPEED;
	new_y = p->y - ray->direction.y * MOVE_SPEED;
	if (map[(int)p->y][(int)new_x] == '0')
		p->x = new_x;
	if (map[(int)new_y][(int)p->x] == '0')
		p->y = new_y;
}
