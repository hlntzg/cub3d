/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:18:35 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/14 17:45:30 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	free_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

static void	free_data(t_data *data)
{
	if (data->map)
		free_map(data);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->player_start)
		free(data->player_start);
}

/*static void	free_images(t_game *game)
{
	if (game->img->no)
		mlx_delete_image(game->mlx, game->img->no);
	if (game->img->so)
		mlx_delete_image(game->mlx, game->img->so);
	if (game->img->we)
		mlx_delete_image(game->mlx, game->img->we);
	if (game->img->ea)
		mlx_delete_image(game->mlx, game->img->ea);
}*/

void	free_game(t_game *game)
{
	free_data(game->data);
	if (game->data)
		free(game->data);
	//free_images(game);
}
