NAME	= cub3D

RM		= rm -f

SRC		= cub3d.c get_next_line.c utils.c parse/map.c \

CFLAGS	=  #-Wall -Wextra -Werror  

OBJ		= $(SRC:.c=.o)

LIBFT	= libft/libft.a

CC		= cc

all		: $(NAME) #clean
			
%.o		: %.c cub3d.h Makefile
			$(CC) $(CFLAGS) -c $<  -o $@

$(LIBFT) :
			make -C libft

$(NAME)	: $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT)  -o $@ -lmlx -framework OpenGL -framework AppKit   

clean	: 
			$(RM) $(OBJ)
			make -C libft/ clean


fclean	: clean
			$(RM) $(NAME)
			make -C libft/ fclean

re		: fclean all

