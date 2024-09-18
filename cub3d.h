# ifndef CUB3D_H
# define CUB3D_H

// #include <minilibx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"
# define BUFFER_SIZE 1024
# define TRUE 1
# define FALSE 0



typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;


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

// utils
// int		till_char(char *s, char c);
char	**strjoin2d(char **str, char *s);
char	*ft_strtrim_end(char const *s1, char const *set);
char	*get_next_line(int fd);
void	free_it(char **s, int i);
int		skip_char(char *s, char c);
int		ft_strlen2d(char **s);
int		is_empty(char *s);
int		my_atoi(char *str);
void	parse_it(char *s, t_data *cub);
void	create_game(t_data *cub);



#endif