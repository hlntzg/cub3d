/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:38:53 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/19 16:22:09 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rendering_game(t_game *game)
{
	set_player(&game->data, &game->player);
	set_map(game); // WIP
	raycasting(game);
	mapping_pixels(game); // WIP
}

void	raycasting(t_game *game)
{
	t_raycast	*ray;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		get_ray_direction(&game->player, ray, x);
		get_delta_distance(&game->player, ray);
		get_steps_distance(&game->player, ray);
		get_wall_distance_and_height(game, ray);
		get_wall_projection_pixels(&game->player, ray);
		get_wall_pixels(game, ray, x);
		x++;
	}
}
