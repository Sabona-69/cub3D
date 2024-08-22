#include "cub3d.h"

int main(int argc, char *argv[])
{
	if (is_empty(argv[1]) == TRUE)
		printf("empty");
	else
		printf("full");
	return 0;
}
