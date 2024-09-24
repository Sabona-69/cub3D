NAME	= cub3D

BNAME	= cub3D_bonus

RM		= rm -f

SRC		= mandatory/cub3d.c mandatory/get_next_line.c mandatory/utils.c mandatory/parse/map.c \

BSRC		= bonus/cub3d_b.c bonus/get_next_line_b.c bonus/utils_b.c bonus/parse/map_b.c \

CFLAGS	=   #-g -fsanitize=address#-Wall -Wextra -Werror 

OBJ		= $(SRC:.c=.o)

BOBJ		= $(BSRC:.c=.o)

LIBFT	= libft/libft.a

CC		= cc

all				: $(NAME) #clean

bonus			: $(BNAME)
			
mandatory/%.o	: mandatory/%.c mandatory/cub3d.h Makefile
			$(CC) $(CFLAGS) -c $<  -o $@

bonus/%.o		: bonus/%.c bonus/cub3d_b.h Makefile
			$(CC) $(CFLAGS) -c $<  -o $@

$(LIBFT) 		:
			make -C libft

$(NAME)			: $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT)  -o $@ -lmlx -framework OpenGL -framework AppKit

$(BNAME)			: $(BOBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(BOBJ) $(LIBFT)  -o $@ -lmlx -framework OpenGL -framework AppKit

clean			: 
			$(RM) $(OBJ) $(BOBJ)
			make -C libft/ clean

fclean			: clean
			$(RM) $(NAME) $(BNAME)
			make -C libft/ fclean

re				: fclean all

