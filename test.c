#include "mlx.h"

int main ()
{
	void	*mlx;
	void	*win;

	 mlx = mlx_init();
	 win = mlx_new_window(mlx, 11 * 32, 15 * 32, "cub3D");
	 mlx_loop(mlx);

}