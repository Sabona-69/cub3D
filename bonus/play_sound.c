#include "../include/cub3d_b.h"

void	play_sound(int status)
{
	char	*av[4];

	av[0] = "/Users/hel-omra/.brew/bin/mpg123";
	av[1] = "-q";
	if (status == OPENING)
		av[2] = "/Users/hel-omra/Documents/cub3D/assets/dkhla.mp3";
	else
		av[2] = "/Users/hel-omra/Documents/cub3D/assets/lahybarek_t.mp3";
	av[3] = NULL;
	if (execve(av[0], av, NULL) == -1)
		perror("execve failed");
}

	// av[2] = "/Users/tbesbess/Desktop/Cub3D_last/assets/r.mp3";
	// av[2] = "/Users/tbesbess/Desktop/Cub3D_last/assets/lahybarek_t.mp3";