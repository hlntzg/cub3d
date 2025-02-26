/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:04:26 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/26 17:04:27 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	game_light(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

    game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_game(game);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_LEFT_CONTROL)
            printf("hi\n");
        else if (keydata.key == MLX_KEY_LEFT_SHIFT)
            printf("hello\n");
        else if (keydata.key == MLX_KEY_RIGHT_CONTROL)
          printf("hi2\n");
        else if (keydata.key == MLX_KEY_RIGHT_SHIFT)
            printf("hello2\n");
        else if (keydata.key == MLX_KEY_UP && game->render->brightness < 1)
            game->render->brightness += 0.1;
        else if (keydata.key == MLX_KEY_DOWN && game->render->brightness > 0)
            game->render->brightness -= 0.1;
    }
}