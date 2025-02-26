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

void	clear_pixel_buffer(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			game->render->pixels[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	rendering_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	clear_pixel_buffer(game);
	move_player(game);
	raycasting(game);
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

int	get_orientation(t_raycast *ray)
{	
	if (ray->direction.y < 0 && ray->boundary == 1)
		return (NORTH);
	if (ray->direction.y > 0 && ray->boundary == 1)
		return (SOUTH);
	if (ray->direction.x < 0 && ray->boundary == 0)
		return (WEST);
	if (ray->direction.x > 0 && ray->boundary == 0)
		return (EAST);
	return (EXIT_FAILURE);
}

// converts wall_x strip into a texture coordinate
// obs: when the wall faces SOUTH or WEST, the ray intersects from the opposite
// side of how the texture is naturally laid out. After the adjustment, the 
// leftmost part of the texture maps correctly to the left edge of the wall
int	get_x_coordinate(t_raycast *ray, int txtr)
{
	int	x;

	x = (int)(ray->wall_x * TEXTURE);
	if (txtr == NORTH || txtr == EAST)
		return (x);
	if (txtr == SOUTH || txtr == WEST)
		return (TEXTURE - x - 1);
	return (EXIT_FAILURE);
}
//light source coming from the North-East (1, -1).
// Normalize the ray direction
// Normalize the light direction
// Compute dot product for shading
// Ensure min brightness (fmax with 0.5)
double	get_shading_factor(t_raycast *ray, t_render *render)
{
	double shading_factor;

	render->light_source.x = 1.0;
	render->light_source.y = -1.0;
	ray->ray_length = sqrt(ray->direction.x * ray->direction.x + ray->direction.y * ray->direction.y);
	ray->norm_ray.x = ray->direction.x / ray->ray_length;
	ray->norm_ray.y = ray->direction.y / ray->ray_length;
	ray->light_length = sqrt(render->light_source.x  * render->light_source.x  + render->light_source.y * render->light_source.y);
	ray->norm_light.x  = render->light_source.x / ray->light_length;
	ray->norm_light.y = render->light_source.y / ray->light_length;
	shading_factor = ray->norm_ray.x * ray->norm_light.x + ray->norm_ray.y * ray->norm_light.y;
	shading_factor = fmax(0.5, shading_factor); 
	return (shading_factor);
}

// Reduce brightness of the color by factor (e.g., 0.6 = 60% brightness)
uint32_t	apply_shading(uint32_t color, t_raycast *ray, t_render *render)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double factor;

	factor = get_shading_factor(ray, render);
	a = (color >> 24) & 0xFF;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

// fixed light source coming from the North-East (1, -1).
// North-facing walls (d.y < 0) get more light.
// South-facing walls (d.y > 0) are darker.
// East-facing walls (d.x > 0) are brighter.
// West-facing walls (d.x < 0) are darker.

// get the pixels of the x wall strip from the corresponding texture;
// store them in the pixel_map
void get_wall_pixels(t_game *game, t_raycast *ray, int x)
{
	int			txtr;
	int			txtr_x;
	double		txtr_y;
	double		txtr_scaling;
	uint32_t	pixel_color;

	txtr = get_orientation(ray);
	txtr_x = get_x_coordinate(ray, txtr);
	txtr_scaling = (double)TEXTURE / fmax(ray->wx_height, 1.0);
	txtr_y = (double)(ray->wx_top_pixel - HEIGHT / 2 + ray->wx_height / 2) * txtr_scaling;

	while (ray->wx_top_pixel < ray->wx_bottom_pixel)
	{
		txtr_y += txtr_scaling;
		pixel_color = game->render->txtr_buf[txtr][(TEXTURE * ((int)txtr_y % TEXTURE)) + txtr_x];
		pixel_color = apply_shading(pixel_color, ray, game->render);
		if (pixel_color > 0)
			game->render->pixels[ray->wx_top_pixel][x] = pixel_color;
		ray->wx_top_pixel++;
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
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return ;
	pixels = (uint32_t *)game->img->pixels;
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
		y++;
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}