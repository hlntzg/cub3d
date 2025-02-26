/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:18:35 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 13:52:50 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_pixels(uint32_t **array)
{
	int i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

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
	if (data)
		free(data);
}

void	free_texture(t_game *game)
{
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
	//if(game->render->txtr_buf)
	//free_pixels(game->render->txtr_buf);
	if(game->render->pixels)
		free_pixels(game->render->pixels);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	if (game->render)
		free(game->render);
}

void	exit_game(t_game *game)
{
	free_game(game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	exit (0);
}
