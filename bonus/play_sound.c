#include "../include/cub3d_b.h"

void play_sound()
{
    char *cmd = "/Users/tbesbess/homebrew/bin/mpg123";
    char *av[3];
    char *env[] = { NULL };

    av[0] = cmd;
    // av[1] = "/Users/hel-omra/Dedsktop/Cub3D_last/assets/r.mp3";
    av[1] = "/Users/tbesbess/Desktop/Cub3D_last/assets/r.mp3";
    av[2] = NULL;

    if (execve(cmd, av, env) == -1) {
        perror("execve failed");
    }
}
void play_sound_door()
{
    char *cmd = "/Users/tbesbess/homebrew/bin/mpg123";
    char *av[3];
    char *env[] = { NULL };

    av[0] = cmd;
    // av[1] = "/Users/hel-omra/Dedsktop/Cub3D_last/assets/r.mp3";
    av[1] = "/Users/tbesbess/Desktop/Cub3D_last/assets/lahybarek_t.mp3";
    av[2] = NULL;

    if (execve(cmd, av, env) == -1) {
        perror("execve failed");
    }
}