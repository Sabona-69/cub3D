NAME	= cub3D

BNAME	= cub3D_bonus

CC		= cc 

RM		= rm -f

OBJ		= $(SRC:.c=.o)

BOBJ	= $(BSRC:.c=.o)

SRC		= mandatory/cub3d.c mandatory/get_next_line.c mandatory/parse/parse_utils.c\
			mandatory/parse/map.c mandatory/parse/store_instructions.c mandatory/parse/store_map.c  mandatory/create_game.c \
			mandatory/game_utils.c mandatory/game_utils2.c mandatory/garbage_collector.c  \
			mandatory/movement.c mandatory/raycast.c mandatory/textures.c mandatory/walls.c

BSRC		= bonus/cub3d_b.c bonus/get_next_line_b.c bonus/parse/parse_utils_b.c\
			bonus/parse/map_b.c bonus/parse/store_instructions_b.c bonus/parse/store_map_b.c bonus/mini_map.c\
			bonus/create_game_b.c bonus/raycast_b.c bonus/movement_b.c bonus/game_utils_b.c bonus/game_utils_b2.c \
			bonus/game_utils_b3.c bonus/textures_b.c bonus/walls_b.c bonus/garbage_collector_b.c bonus/play_sound.c \

CFLAGS	=  -Ofast -Wall -Werror -Wextra

LIBFT	= libft/libft.a

LIBFT_B	= libft_b/libft_b.a

INCLUDE = include/cub3d_b.h libft/libft.h

INCLUDE_B = include/cub3d_b.h libft/libft.h

MLX42 = /Users/$(USER)/MLX42/build/libmlx42.a

GLFW = /Users/$(USER)/homebrew/opt/glfw/lib
all: $(NAME)


bonus: $(BNAME)

mandatory/%.o: mandatory/%.c $(INCLUDE)
			$(CC) $(CFLAGS) -c $<  -o $@

bonus/%.o: bonus/%.c $(INCLUDE_B)
			$(CC) $(CFLAGS) -c $<  -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) -Iinclude -lglfw -L$(GLFW) -o $(NAME)


$(BNAME): $(BOBJ) $(LIBFT_B)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBFT_B) $(MLX42) -Iinclude -lglfw -L$(GLFW) -o $(BNAME)

$(LIBFT):
			make -C libft

$(LIBFT_B):
			make -C libft_b

clean: 
	$(RM) $(OBJ) $(BOBJ)
	make -C libft/ clean
	make -C libft_b/ clean

fclean: clean
	$(RM) $(NAME) $(BNAME)
	make -C libft/ fclean
	make -C libft_b/ fclean

re: fclean all