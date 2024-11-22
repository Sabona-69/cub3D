#include "../include/cub3d_b.h"

// void    play_sound()
// {
//     char *cmd;
//     char **av;
//     char **env;

//     cmd = "/Users/tbesbess/homebrew/bin/mpg123";
//     av[0] = "/Users/tbesbess/homebrew/bin/mpg123";
//     printf ("hna\n");
//     av[1] = "/Users/tbesbess/Desktop/r.mp3";
//     av[2] = NULL;
//     env[0] = NULL;
//     if (execve("/Users/tbesbess/homebrew/bin/mpg123", av, env) == -1)
//         printf ("hna\n");
//         // exit (1);
// }


void play_sound()
{
    char *cmd = "/Users/tbesbess/homebrew/bin/mpg123";
    char *av[3];
    char *env[] = { NULL };

    av[0] = cmd;
    av[1] = "/Users/tbesbess/Desktop/masira1.mp3";
    av[2] = NULL;

    if (execve(cmd, av, env) == -1) {
        perror("execve failed");
    }
}
