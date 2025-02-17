/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:21 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/17 14:07:26 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <string.h>

# define WIDTH		1920
# define HEIGHT		1080

typedef struct s_coord
{
	int		x;
	int		y;
}	t_coord;

typedef struct s_txtr
{
	mlx_texture_t	*no;
	mlx_texture_t	*ea;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ce;
	mlx_texture_t	*fl;
}	t_txtr;

typedef struct s_img
{
	mlx_image_t	*no;
	mlx_image_t	*ea;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ce;
	mlx_image_t	*fl;
}	t_img;

typedef struct s_data
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		**map;
	char		**map_access;
	char		dir_player;
	int			lines;
	int			columns;
	uint32_t	floor;
	uint32_t	ceiling;
	t_coord		player_start;
	t_coord		map_size;
}	t_data;

typedef struct s_game
{
	mlx_t	*mlx;
	t_data	*data;
	t_txtr	*txtr;
	t_img	*img;
}	t_game;

/* MAIN */

/* INIT_GAME */
int			init_game(t_game *game);

/* GAME */
void		game_events(mlx_key_data_t keydata, void *param);

/* VALIDATE_CUB */
int			validate_cub(char *map_name, t_game *game);
int			validate_extension(char *map_name, char a, char b, char c);

/* MAP */
int			read_copy_map(char **cub_content, t_data *data);

/* VALIDATE_MAP */
int			valid_chars(t_data *data);

/* VALIDATE_WALLS */
int			is_accessible(t_data *data);

/* VALIDATE_TEXTURES */
int			validate_texture(char **map, t_game *game);

/* VALIDATE_RGB */
int			validate_rgb(char **map, t_game *game);

/* UTILS_VALIDATE */
char		*extract(char **map, int i, int j, char *extract);
int			is_duplicate_rgb(uint32_t rbg_type);
uint32_t	create_color(int r, int g, int b);
int			check_rgb(char *rgb);
int			validate_rgb_split(char **rgb_split);

/* READ_MAP */
char		**read_map(char *path);

/* IMAGES */
int			get_texture(t_game *game);

/* FREE */
void		free_char_array(char **array);
void		free_game(t_game *game);
void		exit_game(t_game *game);

#endif
