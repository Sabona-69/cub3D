/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesbess <tbesbess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:10:15 by tbesbess          #+#    #+#             */
/*   Updated: 2024/10/27 10:57:12 by tbesbess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

// #include <minilibx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "../libft/libft.h"
# include "../../../MLX42/include/MLX42/MLX42.h"

# define BUFFER_SIZE	1024
# define TRUE			1
# define FALSE			0

# define HEIGHT			1440
# define WIDTH			2560
# define FOV			90
# define TILE_SIZE		32
# define ROTATION_SPEED 0.045
# define MOVE_SPEED		5
# define COLLISION		3

//colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

typedef enum e_status
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	TURN_RIGHT,
	TURN_LEFT,
}	t_status;

typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

typedef struct s_pos_d
{
	double		x;
	double		y;
}	t_pos_d;
typedef struct s_data
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		height;
	int		width;
	char	player_facing;
	t_pos	player_postion;
	int		F[3];
	int		C[3];
	int		fd;
	char	*line;
}	t_data;

typedef	struct s_pl
{
	double		direction;
	t_pos_d		start;
	t_pos_d		move;
	double		view;
	t_status	walk;
	t_status	turn;
} t_pl;

typedef struct s_game
{
	mlx_t		*win;
	mlx_image_t	*img;
	// t_tx		*tx;
	t_data		*data;
	t_pl		*player;
	t_ray		*rays;
	t_flag		flag;
}	t_game;