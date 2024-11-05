NAME	= cub3D

CC		= cc 

RM		= rm -f

OBJ		= $(SRC:.c=.o)

BOBJ	= $(BSRC:.c=.o)

SRC		= mandatory/cub3d.c mandatory/get_next_line.c mandatory/parse/parse_utils.c\
			mandatory/parse/map.c mandatory/parse/store_instructions.c mandatory/parse/store_map.c mandatory/parse/check_walls.c \
			mandatory/create_game.c mandatory/raycast.c mandatory/movement.c mandatory/game_utils.c mandatory/walls.c \

BSRC		= bonus/cub3d_b.c bonus/get_next_line_b.c bonus/parse/parse_utils_b.c\
			bonus/parse/map_b.c bonus/parse/store_instructions_b.c bonus/parse/store_map_b.c bonus/parse/check_walls_b.c \
			bonus/create_game_b.c bonus/raycast_b.c bonus/movement_b.c bonus/game_utils_b.c bonus/walls_b.c \

CFLAGS	=  -fsanitize=address#-Wall -Werror -Wextra

BNAME	= cub3D_bonus

LIBFT	= libft/libft.a

all: $(NAME) clean

bonus: $(BNAME)

mandatory/%.o: mandatory/%.c mandatory/cub3d.h Makefile leaks.h
			$(CC) $(CFLAGS) -c $<  -o $@

bonus/%.o: bonus/%.c bonus/cub3d_b.h Makefile leaks.h
			$(CC) $(CFLAGS) -c $<  -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -o $(NAME)


$(BNAME): $(BOBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBFT) /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -o $(BNAME)

$(LIBFT):
			make -C libft

clean: 
	$(RM) $(OBJ) $(BOBJ)
	make -C libft/ clean

fclean: clean
	$(RM) $(NAME) $(BNAME)
	make -C libft/ fclean

re: fclean all
