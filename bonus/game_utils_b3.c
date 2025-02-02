/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_b3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:33:08 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:33:09 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_b.h"

int	check_collision(t_game *game, int x, int y)
{
	int	top_left;
	int	top_right;
	int	bottom_left;
	int	bottom_right;

	top_left = is_wall(x - COLLISION, y - COLLISION, game);
	top_right = is_wall(x + COLLISION, y - COLLISION, game);
	bottom_left = is_wall(x - COLLISION, y + COLLISION, game);
	bottom_right = is_wall(x + COLLISION, y + COLLISION, game);
	return (top_left || top_right || bottom_left || bottom_right);
}

static mlx_image_t	**generating_frames(t_game *game, char *path, int frames)
{
	mlx_image_t		**new;
	mlx_texture_t	*tx;
	int				i;

	i = 0;
	new = ft_malloc(frames * sizeof(mlx_image_t *), MALLOC);
	if (!new)
		return (NULL);
	while (i < frames)
	{
		tx = mlx_load_png(ft_strjoin(ft_strjoin(path, ft_itoa(i + 1)), ".png"));
		if (!tx)
			exiting(game, "Invalid texture");
		new[i] = mlx_texture_to_image(game->win, tx);
		new[i]->enabled = (i == 0);
		mlx_resize_image(new[i], WIDTH, HEIGHT);
		mlx_image_to_window(game->win, new[i], 0, 0);
		mlx_delete_texture(tx);
		i++;
	}
	return (new);
}

void	init_animation(t_game *game)
{
	game->anim->i = 0;
	game->anim->img = generating_frames(game, ANIMATION_PATH, FRAMES);
	if (!game->anim->img)
		exiting(game, "Malloc failed");
}

void	animation(t_game *game)
{
	int	current_frame;
	int	previous_frame;

	current_frame = game->anim->i % FRAMES;
	previous_frame = (current_frame - 1 + FRAMES) % FRAMES;
	game->anim->img[current_frame]->enabled = true;
	game->anim->img[previous_frame]->enabled = false;
	game->anim->i = (game->anim->i + 1) % FRAMES;
}
