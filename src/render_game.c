/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:38:53 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/26 13:34:04 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rendering_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	clear_pixel_buffer(game);
	move_player(game);
	raycasting(game);
	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	if (!game->img)
		return ;
	rendering_image(game);
}

void	raycasting(t_game *game)
{
	t_raycast	*ray;
	int			x;

	x = 0;
	ray = game->ray;
	while (x < game->win_w)
	{
		get_ray_direction(game, game->player, ray, x);
		get_delta_distance(game->player, ray);
		get_steps_distance(game->player, ray);
		get_wall_distance_and_height(game, ray);
		get_wall_projection_pixels(game, game->player, ray);
		get_wall_pixels(game, ray, x);
		x++;
	}
}

// process and render the whole image from the pixel map (screen pixels)
// check if the pixel is in wall, floor or ceiling position
void	rendering_image(t_game *game)
{
	uint32_t	color;
	uint32_t	*pixels;
	uint32_t	x;
	uint32_t	y;

	color = 0;
	pixels = (uint32_t *)game->img->pixels;
	y = 0;
	while (y < (uint32_t)game->win_h)
	{
		x = 0;
		while (x < (uint32_t)game->win_w)
		{
			if (game->render->pixels[y][x] > 0)
				color = game->render->pixels[y][x];
			else if (y < (uint32_t)game->win_h / 2)
				color = game->data->ceiling;
			else if (y > (uint32_t)game->win_h / 2)
				color = game->data->floor;
			pixels[y * (uint32_t)game->win_w + x] = color;
			x++;
		}	
		y++;
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
