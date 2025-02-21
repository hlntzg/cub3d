/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:18:35 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/21 14:15:02 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static void	free_pixels(t_game *game)
// {
// 	int i;

// 	if (!game->render->pixels)
// 		return;

// 	i = 0;
// 	while (i < HEIGHT)
// 	{
// 		free(game->render->pixels[i]);
// 		i++;
// 	}
// 	free(game->render->pixels);
// 	game->render->pixels = NULL;
// }

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_data(t_data *data)
{
	if (data->map)
		free_char_array(data->map);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
}

void	free_images(t_game *game)
{
	/*if (game->img->no)
		mlx_delete_image(game->mlx, game->img->no);
	if (game->img->so)
		mlx_delete_image(game->mlx, game->img->so);
	if (game->img->we)
		mlx_delete_image(game->mlx, game->img->we);
	if (game->img->ea)
		mlx_delete_image(game->mlx, game->img->ea);*/
	if (game->txtr->no)
		mlx_delete_texture(game->txtr->no);
	if (game->txtr->so)
		mlx_delete_texture(game->txtr->so);
	if (game->txtr->we)
		mlx_delete_texture(game->txtr->we);
	if (game->txtr->ea)
		mlx_delete_texture(game->txtr->ea);
	free(game->txtr);
}

void	free_game(t_game *game)
{
	free_data(game->data);
	if (game->data)
		free(game->data);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	if (game->render)
		free(game->render);
	// if(game->render->pixels)
	// 	free_pixels(game);
}

void	exit_game(t_game *game)
{
	free_game(game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	exit (0);
}
