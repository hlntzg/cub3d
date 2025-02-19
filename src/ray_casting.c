/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:49:26 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/19 15:08:07 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	get_ray_direction(t_player *player, t_raycast *ray, int x)
{
	ray->camera = (2 * x) / ((double)WIDTH - 1);
	ray->direction.x = (player->d.x + player->p.x) * ray->camera;
	ray->direction.y = (player->d.y + player->p.y) * ray->camera;
}

void	get_delta_distance(t_player *player, t_raycast *ray)
{
	ray->delta.x = fabs(1 / ray->direction.x);
	ray->delta.y = fabs(1 / ray->direction.y);
	ray->map.x = (int)player->position.x;
	ray->map.y = (int)player->position.y;
}

// calculates the initial steps and distances needed for raycasting in both the
// x and y directions, based on the player's position and the ray's direction
void	get_steps_distance(t_player *player, t_raycast *ray)
{
	if (ray->direction.x > 0)
	{
		ray->step_dir.x = 1;
		ray->step.x = (ray->map.x + 1.0 - player->position.x) * ray->delta.x;
	}
	else
	{
		ray->step_dir.x = -1;
		ray->step.x = (player->position.x - ray->map.x) * ray->dalta.x;
	}
	if (ray->direction.y > 0)
	{
		ray->step_dir.y = 1;
		ray->step.y = (ray->map.y + 1.0 - player->position.y) * ray->delta.y;
	}
	else
	{
		ray->step_dir.y = -1;
		ray->step.y = (player->position.y - ray->map.y) * ray->dalta.y;
	}
}

// step tracks the distance to the next grid line, so
// subtracting delta gives the correct distance to the wall	
void	get_wall_distance_and_height(t_game *game, t_raycast *ray)
{
	while (1)
	{
		if (ray->step.y > ray->step.x)
		{
			ray->boundary = 0;
			ray->step.x += ray->delta.x;
			ray->map.x += ray->step_dir.x;
		}
		else
		{
			ray->boundary = 1;
			ray->step.y += ray->delta.y;
			ray->map.y += ray->step_dir.y;
		}
		if (map[ray->map.y][ray->map.x] == '1') // y, x not x, y ????
			break ;
	}
	if (ray->boundary == 0)
		ray->wx_distance = ray->step.x - ray->delta.x;
	if (ray->boundary == 1)
		ray->wx_distance = ray->step.y - ray->delta.y;
	ray->wx_height = (int)(HEIGHT / ray->distance_to_the_Wall);
}

// pixel top-left (0,0), pixel bottom-right (WIDTH, HEIGHT)
void	get_wall_projection_pixels(t_player *player, t_raycast *ray)
{
	int	half_window;
	int	half_wall;

	half_window = HEIGHT / 2;
	half_wall = ray->wx_height / 2;
	ray->wx_top_pixel = half_window - half_wall;
	ray->wx_bottom_pixel = half_window + half_wall;
	if (ray->wx_top_pixel < 0)
		ray->wx_top_pixel = 0;
	if (ray->wx_bottom_pixel > HEIGHT)
		ray->wx_bottom_pixel = HEIGHT;
	if (ray->boundary == 0)
		ray->wall_x = ray->direction.y * ray->wx_distance + player->position.y;
	if (ray->boundary == 1)
		ray->wall_x = ray->direction.x * ray->wx_distance + player->position.x;
}
