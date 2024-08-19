NAME	= cub3d

RM		= rm -f

SRC		= cub3d.c get_next_line.c utils.c\

CFLAGS	= #-fsanitize=address -g3 #-Wall -Wextra -Werror

OBJ		= $(SRC:.c=.o)

LIBFT	= libft/libft.a

CC		= cc

all		: $(NAME) #clean
			
%.o		: %.c cub3d.h Makefile
			$(CC) $(CFLAGS) -c $<  -o $@

$(LIBFT) :
			make -C libft

$(NAME)	: $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

clean	: 
			$(RM) $(OBJ)
			make -C libft/ clean


fclean	: clean
			$(RM) $(NAME)
			make -C libft/ fclean

re		: fclean all

