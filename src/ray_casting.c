/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:49:26 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/25 16:32:27 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	get_ray_direction(t_player *player, t_raycast *ray, int x)
{
	ray->camera = 2 * x / (double)WIDTH - 1;
	//printf("cam %f\n", ray->camera);
	//printf("player dx = %f :: player px = %f\n", player->d.x, player->p.x);
	//printf("player dy = %f :: player py = %f\n", player->d.y, player->p.y);
	ray->direction.x = player->d.x + player->p.x * ray->camera;
	ray->direction.y = player->d.y + player->p.y * ray->camera;
	//printf("dir x %f\n", ray->direction.x);
	//printf("dir y %f\n", ray->direction.y);
}

void	get_delta_distance(t_player *player, t_raycast *ray)
{
	ray->delta.x = fabs(1 / ray->direction.x);
	ray->delta.y = fabs(1 / ray->direction.y);
	// printf("delta x %f\n", ray->delta.x);
	// printf("delta y %f\n", ray->delta.y);
	ray->map.x = (int)player->position.x;
	ray->map.y = (int)player->position.y;
//	printf("map x %d\n", ray->map.x);
//	printf("map y %d\n", ray->map.y);
}

// calculates the initial steps and distances needed for raycasting in both the
// x and y directions, based on the player's position and the ray's direction
void	get_steps_distance(t_player *player, t_raycast *ray)
{
	if (ray->direction.x >= 0)
	{
		ray->step_dir.x = 1;
		ray->step.x = (ray->map.x + 1.0 - player->position.x) * ray->delta.x;
	}
	else
	{
		ray->step_dir.x = -1;
		ray->step.x = (player->position.x - ray->map.x) * ray->delta.x;
	}
	if (ray->direction.y >= 0)
	{
		ray->step_dir.y = 1;
		ray->step.y = (ray->map.y + 1.0 - player->position.y) * ray->delta.y;
	}
	else
	{
		ray->step_dir.y = -1;
		ray->step.y = (player->position.y - ray->map.y) * ray->delta.y;
	}
//	printf("step x %f\n", ray->step.x);
//	printf("step y %f\n", ray->step.y);
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
		// if (ray->map.x < 0 || ray->map.x >= game->data->columns || ray->map.y < 0
		// 	|| ray->map.y >= game->data->lines)
		// 	break ;
		if (game->data->map[ray->map.y][ray->map.x] == '1')
			break ;
	}
	if (ray->boundary == 0)
		ray->wx_distance = ray->step.x - ray->delta.x;
	if (ray->boundary == 1)
		ray->wx_distance = ray->step.y - ray->delta.y;
	//printf("wx dist %f\n", ray->wx_distance);
	//sleep(5);
	ray->wx_height = (int)(HEIGHT / ray->wx_distance); //-((WIDTH / 2) / tan(30)) / ray->wx_distance;
	//printf("wx height %d\n", ray->wx_height);
}

// pixel top-left (0,0), pixel bottom-right (WIDTH, HEIGHT)
void	get_wall_projection_pixels(t_player *player, t_raycast *ray)
{
	int	half_window;
	int	half_wall;

	half_window = HEIGHT / 2;
	half_wall = (int) ray->wx_height / 2;
	ray->wx_top_pixel = half_window - half_wall;
	ray->wx_bottom_pixel = half_window + half_wall;
	if (ray->wx_top_pixel < 0)
		ray->wx_top_pixel = 0;
	if (ray->wx_bottom_pixel > HEIGHT)
		ray->wx_bottom_pixel = HEIGHT;// - 1;
	if (ray->boundary == 0)
		ray->wall_x = ray->direction.y * ray->wx_distance + player->position.y;
	if (ray->boundary == 1)
		ray->wall_x = ray->direction.x * ray->wx_distance + player->position.x;
	ray->wall_x -= floor(ray->wall_x);
}
