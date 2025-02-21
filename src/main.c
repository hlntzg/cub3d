/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:41:10 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/21 11:30:30 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	start_game(t_game *game)
{
	if (get_texture(game) == 1)
		return (EXIT_FAILURE);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	mlx_key_hook(game->mlx, &game_events, game);
	mlx_loop_hook(game->mlx, &rendering_game, game);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid arguments.", 2);
		ft_putstr_fd("Please use the format './cub3D *.cub'\n", 2);
		return (EXIT_FAILURE);
	}
	if (init_game(&game) == 1)
		return (free_game(&game), EXIT_FAILURE);
	if (validate_cub(argv[1], &game) == 1)
		return (free_game(&game), EXIT_FAILURE);
	if (start_game(&game) == 1)
		return (exit_game(&game), EXIT_FAILURE);
	mlx_loop(game.mlx);
	exit_game(&game);
	return (EXIT_SUCCESS);
}
