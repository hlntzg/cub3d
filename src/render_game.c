/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:38:53 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/21 11:30:08 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rendering_game(void *param)
{
	t_game *game;
	
	game = (t_game *)param;
	set_player(&game->data, &game->player);
	move_player(game);
	set_pixel_map(game);
	raycasting(game);
	rendering_image(game); // WIP
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
		get_x_pixels_buffer(game, ray, x);
		x++;
	}
}

// set up a 2D array pixel map for the screen - window(width, height)
void	set_pixel_map(t_game *game)
{
	int	y;

	y = 0;
	game->render->pixels = malloc(sizeof(int) * (HEIGHT + 1));
	if (!game->render->pixels)
		return ; // return NULL
	while (y < HEIGHT)
	{
		game->render->pixels[y] = calloc(sizeof(int), WIDTH);
		if (!game->render->pixels[y])
			return ; // free array
		y++;
	}
}

int		get_orientation(t_raycast *ray)
{	
	if (ray->direction.y < 0 && ray->boundary == 1)
		return (NORTH);
	if (ray->direction.y > 0 && ray->boundary == 1)
		return (SOUTH);
	if (ray->direction.x < 0 && ray->boundary == 0)
		return (WEST);
	if (ray->direction.x > 0 && ray->boundary == 0)
		return (EAST);
}

// converts wall_x strip into a texture coordinate
// obs: when the wall faces SOUTH or WEST, the ray intersects from the opposite
// side of how the texture is naturally laid out. After the adjustment, the leftmost
// part of the texture maps correctly to the left edge of the wall
int	get_x_coordinate(t_raycast *ray, int txtr)
{
	int	x;

	x = (int)(ray->wall_x * TXTR_PIXEL);
	if (txtr == NORTH || txtr == EAST)
		return (x);
	if (txtr == SOUTH || txtr == WEST)
		return (TXTR_PIXEL - x - 1);
}

// get the pixels of the x wall strip from the corresponding texture;
// store them in the pixel_map
void	get_wall_pixels(t_game *game, t_raycast *ray, int x)
{
	int		txtr;
	int		txtr_x;
	double	txtr_y;
	double	txtr_scaling;
	int		pixel_color;

	ray->wall_x = ray->wall_x - (floor(ray->wall_x));
	txtr = get_orientation(ray);
	txtr_x = get_x_coordinate(ray, txtr);
	txtr_scaling = TXTR_PIXEL / ray->wx_height;
	txtr_y = (ray->wx_top_pixel - HEIGHT / 2 + ray->wx_height / 2) * txtr_scaling;
	while (ray->wx_top_pixel < ray->wx_bottom_pixel)
	{
		txtr_y += txtr_scaling;
		pixel_color = (game->render->txtr_buf)[txtr][(TXTR_PIXEL * ((int)txtr_y & (TXTR_PIXEL - 1))) + txtr_x];
		// color adjustments ?
		if (pixel_color >= 0)
			game->render->pixels[ray->wx_top_pixel][x] = pixel_color;
		ray->wx_top_pixel++;
	}
}

// process and render the whole image from the pixel map (screen pixels)
// check if the pixel is in wall, floor or ceiling position
void	rendering_image(t_game *game)
{
	mlx_image_t	*img;
	uint32_t	color;
	uint32_t	*pixels;
	uint32_t	x;
	uint32_t	y;
	
	color = 0;
	img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img)
		return ;
	pixels = (uint32_t *)img->pixels;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (game->render->pixels[y][x] > 0)
				color = game->render->pixels[y][x];	
			else if (y < HEIGHT / 2)
				color = game->data->ceiling;
			else if (y > HEIGHT / 2)
				color = game->data->floor;
			pixels[y * WIDTH + x] = color;
			x++;
		}
//		mlx_put_pixel(img, x, y, color);	
		y++;
	}
	mlx_image_to_window(game->mlx, img, 0, 0);
}
