/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:40:36 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/17 13:58:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	game_events(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		free_game(game);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		printf("key pressed: A\n");
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		printf("key pressed: D\n");
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		printf("key pressed: S\n");
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		printf("key pressed: W\n");
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		printf("key pressed: LEFT\n");
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		printf("key pressed: RIGHT\n");
}
