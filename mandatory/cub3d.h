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

# define HEIGHT			900
# define WIDTH			1600
# define VIEW			60
# define TILE_SIZE		32
# define ROTATION_SPEED 0.045
# define MOVE_SPEED		5
# define COLLISION		3

//colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

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


typedef struct s_data
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	player_facing;
	t_pos	player_postion;
	int		F[3];
	int		C[3];
	int		fd;
	char	*line;
}   t_data;


typedef struct s_texture
{
	char	*alias;
	char	*src;
}	t_texture;

typedef struct s_tx
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
}	t_tx;

typedef	struct s_pl
{
	double		direction;
	t_pos		star;
	t_pos		move;
	double		view;
	t_status	walk;
	t_status	turn;
} t_pl;

typedef struct s_ray
{
	int			index;
	double		angl;
	t_pos		h_wall;
	t_pos		v_wall;
	double		distance;
	double		angle;
	int			up;
	int			down;
	int			right;
	int			left;
	int			was_hit_vertical;
}	t_ray;

typedef struct s_game
{
	mlx_t		*win;
	mlx_image_t	*img;
	t_tx		*tx;
	t_texture	t_texture;
	t_data		*data;
	t_pl		*player;
	t_ray		*rays;
	bool		isGameRunning;
}	t_game;



// utils
// int		till_char(char *s, char c);
void	exiting(t_data *cub, int status);
char	**strjoin2d(char **str, char *s);
char	*ft_strtrim_end(char const *s1, char const *set);
char	*get_next_line(int fd);
void	free2d(char **s, int i);
int		skip_char(char *s, char c);
int		ft_strlen2d(char **s);
int		is_empty(char *s);
int		my_atoi(char *str);
void	parse_it(char *s, t_data *cub);
void    set_player(t_game *game);
void    create_game(t_game *game);



#endif