CC 			= cc

CFLAGS 		=  -Wall -Wextra -Werror

FILES 		= ft_isalnum_b.c ft_isalpha_b.c ft_isascii_b.c ft_isdigit_b.c ft_isprint_b.c ft_memmove_b.c \
			  ft_strlen_b.c ft_memset_b.c ft_bzero_b.c ft_memcpy_b.c ft_strlcpy_b.c ft_strlcat_b.c \
			  ft_toupper_b.c ft_tolower_b.c ft_strchr_b.c ft_strrchr_b.c ft_strncmp_b.c ft_memchr_b.c \
			  ft_memcmp_b.c ft_strnstr_b.c ft_atoi_b.c ft_calloc_b.c ft_strdup_b.c ft_substr_b.c \
			  ft_strjoin_b.c ft_strtrim_b.c ft_split_b.c ft_itoa_b.c ft_strmapi_b.c ft_striteri_b.c \
			  ft_putchar_fd_b.c ft_putstr_fd_b.c ft_putendl_fd_b.c ft_putnbr_fd_b.c ft_strcmp_b.c ../bonus/garbage_collector_b.c \

RM 			= rm -f

AR 			= ar cr

OBJ 		= $(FILES:.c=.o)

NAME		= libft.a

all 	: $(NAME)

$(NAME) : $(OBJ)
		$(AR) $(NAME) $(OBJ)

%.o 	: %.c libft_b.h
		$(CC) $(CFLAGS) -c $< -o $@

clean 	:
		$(RM) $(OBJ)

fclean 	: clean
		$(RM) $(NAME)

re		: fclean all

.PHONY	: clean