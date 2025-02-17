/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:52 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/14 15:45:06 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_texture(t_game *game)
{
	game->txtr->no = mlx_load_png(game->data->no);
	game->txtr->so = mlx_load_png(game->data->so);
	game->txtr->we = mlx_load_png(game->data->we);
	game->txtr->ea = mlx_load_png(game->data->ea);
	if (!game->txtr->no || !game->txtr->so ||!game->txtr->we ||!game->txtr->ea)
		return (ft_putstr_fd("Error\nFailed to load txtr\n", 2), EXIT_FAILURE);
	game->img->no = mlx_texture_to_image(game->mlx, game->txtr->no);
	game->img->so = mlx_texture_to_image(game->mlx, game->txtr->so);
	game->img->we = mlx_texture_to_image(game->mlx, game->txtr->we);
	game->img->ea = mlx_texture_to_image(game->mlx, game->txtr->ea);
	if (!game->img->no || !game->img->so ||!game->img->we ||!game->img->ea)
		return (ft_putstr_fd("Error\nFailed to load image\n", 2), EXIT_FAILURE);
	if (game->txtr->no)
		mlx_delete_texture(game->txtr->no);
	if (game->txtr->so)
		mlx_delete_texture(game->txtr->so);
	if (game->txtr->we)
		mlx_delete_texture(game->txtr->we);
	if (game->txtr->ea)
		mlx_delete_texture(game->txtr->ea);
	return (EXIT_SUCCESS);
}
