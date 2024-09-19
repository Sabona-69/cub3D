#include "cub3d.h"


// void draw_square(void *init, void *window, int x, int y, int color)
// {
//     int i = 0;
//     while (i < 32)
// 	{
//         int j = 0;
//         while (j < 32)
// 		{
//             mlx_pixel_put(init, window, x + i, y + j, color);
//             j++;
//         }
//         i++;
//     }
// }

// void draw_circle(void *init, void *window, int x, int y, int radius, int color)
// {
//     int i = -radius;
//     while (i <= radius)
// 	{
//         int j = -radius;
//         while (j <= radius)
// 		{
//             if (i * i + j * j <= radius * radius)
//                 mlx_pixel_put(init, window, x + i, y + j, color);
//             j++;
//         }
//         i++;
//     }
// }

// void create_game(t_data *cub)
// {
//     int i, j;
//     void *init = mlx_init();
//     void *window = mlx_new_window(init, 32 * 36, 15 * 32, "cub3d");

//     i = 0;
//     while (cub->map[i])
// 	 {
//         j = 0;
//         while (cub->map[i][j])
// 		{
//             if (cub->map[i][j] == '0') 
//                 draw_square(init, window, j * 32, i * 32,0x00FFFFFF ); // Black square
//             if (cub->map[i][j] == '1')
//                 draw_square(init, window, j * 32, i * 32, 0x00000000); // White square
//             if (ft_strchr("EWSN", cub->map[i][j]))
// 			{
//                 draw_square(init, window, j * 32, i * 32,0x00FFFFFF ); // Black square
//                 draw_circle(init, window, j * 32 + 16, i * 32 + 16, 4, 0x00FF0000); // Red circle
// 			}
//             j++;
//         }
//         i++;
//     }
//     mlx_loop(init);
// }


#include <string.h>

int main(int ac, char **av)
{
	t_data *cub;
	// atexit(f);
	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return (printf("Please Insert \"./cub\" + valid map\n"), 1);
	cub = malloc(sizeof(t_data));
	if (!cub)
		return (ft_putstr_fd("malloc failed ", 2), 1);
	ft_memset(cub, 0, sizeof(t_data));
	// (1) && (cub->C[0] = -1, cub->F[0] = -1);
	parse_it(av[1], cub);
	// create_game(cub);
	// raycasti 
}