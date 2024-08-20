# ifndef CUB3D_H
# define CUB3D_H

// #include <minilibx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "libft/libft.h"
# define BUFFER_SIZE 1024

// utils
// int		till_char(char *s, char c);
int		skip_char(char *s, char c);
char	*ft_strtrim_end(char const *s1, char const *set);
int		ft_strlen2d(char **s);
void	free_it(char **s, int i);
char	**strjoin2d (char **str, char *s);
int	my_atoi(char *str);

char	*get_next_line(int fd);

typedef struct s_data
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		fd;
	int		F[3];
	int		C[3];
}   t_data;
#endif