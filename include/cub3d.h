# ifndef CUB3D_H
# define CUB3D_H
// #include "../leaks.h"


# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <sys/time.h>
# include "garbage_collector_b.h"
# include "../libft/libft.h"
# include "../../../MLX42/include/MLX42/MLX42.h"

# define BUFFER_SIZE	1024
# define TRUE			1
# define FALSE			0

# define HEIGHT			1440
# define WIDTH			2560
# define FOV			60
# define TILE_SIZE		32
# define ROTATION_SPEED 0.045
# define MOVE_SPEED		4
# define COLLISION		3
# define ANIMATION_DELAY 150
# define FRAMES 10

// colors

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"


typedef struct s_game t_game;

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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		height;
	int		width;
	char	player_facing;
	t_pos	player_postion;
	int		f[3];
	int		c[3];
	int		fd;
	char	*line;
	t_game	*game;
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

typedef struct s_tx
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
}	t_tx;

typedef struct s_ray
{
	int			index;
	double		angl;
	t_pos_d		h_wall;
	t_pos_d		v_wall;
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
	t_data		*data;
	t_pl		*player;
	t_ray		*rays;
	int			mouse_on;
}	t_game;

// Utils
void	exiting(t_game *game, char *message);

char	**strjoin2d(char **str, char *s);
char	*ft_strtrim_end(char const *s1, char const *set);
char	*get_next_line(int fd);
int		skip_char(char *s, char c);
int		ft_strlen2d(char **s);
int		is_empty(char *s);

// Parse

void	parse_it(char *s, t_game *game);
void	store_instructions(char *s, t_data *data);
void	check_empty_map(t_data *data);
void	store_map(t_data *data);
void	check_walls(char **map, t_game *game);
void	check_space(char **map, t_game *game);


// Game utils
void			my_pixel_put(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void			init_animation(t_game *game);
mlx_texture_t	*get_texture(t_game *game);
int				get_texture_x(mlx_texture_t *texture, t_game *game);
int				get_texture_y(mlx_texture_t *texture, t_game *game, int y, int wall_h);
void			ft_clear_img(mlx_image_t *img);
void			set_player(t_game *game);
void			handle_key(mlx_key_data_t keydata, void *param);
void			movement(t_game *game, double move_x, double move_y);
int				is_wall(double x, double y, t_game *game);
void			projected_wall(t_game *game);
uint32_t		reverse_bytes(uint32_t c);
uint32_t		ft_get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
double			calcul_distance(t_pos_d start, t_pos_d end);
double			normalize_angle(double angle);

// Game
void			raycasting(t_game *game);
void			create_game(t_game *game);
void			adjust_step(t_game *game, t_pos_d *delta, int is_vertical);


//mini map

#endif