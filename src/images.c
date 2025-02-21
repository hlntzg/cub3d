/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:52 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/21 14:48:53 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

uint32_t	store_color(int i, int j, mlx_texture_t *texture)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	index = (i * texture->width + j) * 4;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

int	set_texture_buffer(t_game *game, mlx_texture_t *texture, int orientation)
{
	uint32_t	*pixels;
	uint32_t	i;
	uint32_t	j;

	i = 0;
	pixels = ft_calloc(texture->height * texture->width, sizeof(uint32_t));
	if (!pixels)
		return (EXIT_FAILURE);
	while (i < texture->height)
	{
		j = 0;
		while (j < texture->width)
		{
			pixels[i * texture->width + j] = store_color(i, j, texture);
			j++;
		}
		i++;
	}
	game->render->txtr_buf[orientation] = pixels;
	return (EXIT_SUCCESS);
}

int	get_texture(t_game *game)
{
	//mlx_texture_t	*txtr[4];
	//char			*path[4];
	//int				i;

	// path[0] = (char *)game->txtr->no;
	// path[1] = (char *)game->txtr->so;
	// path[2] = (char *)game->txtr->we;
	// path[3] = (char *)game->txtr->ea;
	// i = 0;
	// while (i < 4)
	// {
	// 	// txtr[i] = mlx_load_png(path[i]);
	// 	// if (!txtr[i])
	// 	// 	return (ft_putstr_fd("Error\nFailed to load texture\n", 2), EXIT_FAILURE);
	// 	if (!(set_texture_buffer(game, txtr[i], i)))
	// 		return (ft_putstr_fd("Error\nFailed to convert texture\n", 2), EXIT_FAILURE);
	// 	mlx_delete_texture(txtr[i]);
	// 	i++;
	// }
	game->txtr->no = mlx_load_png(game->data->no);
	game->txtr->so = mlx_load_png(game->data->so);
	game->txtr->we = mlx_load_png(game->data->we);
	game->txtr->ea = mlx_load_png(game->data->ea);
	if (!game->txtr->no || !game->txtr->so ||!game->txtr->we ||!game->txtr->ea)
		return (ft_putstr_fd("Error\nFailed to load txtr\n", 2), EXIT_FAILURE);
	set_texture_buffer(game, game->txtr->no, 0);
	set_texture_buffer(game, game->txtr->so, 1);
	set_texture_buffer(game, game->txtr->we, 2);
	set_texture_buffer(game, game->txtr->ea, 3);
	free_images(game);
	return (EXIT_SUCCESS);
}
/*
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
}*/
