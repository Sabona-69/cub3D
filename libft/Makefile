# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 10:17:35 by hel-omra          #+#    #+#              #
#    Updated: 2024/08/19 02:10:45 by hel-omra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

FILES 		= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memmove.c \
			  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c \
			  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
			  ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
			  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

BONUS 		= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			  ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
			  ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJ = $(BONUS:.c=.o)

RM 			= rm -rf

AR 			= ar crs

OBJ 		= $(FILES:.c=.o)

NAME		= libft.a

BONUS_OBJ 	= $(BONUS:.c=.o)

ALL 		= $(OBJ) $(BONUS_OBJ)

all 	: $(NAME) clean

$(NAME) : $(OBJ)
		$(AR) $(NAME) $(OBJ)

bonus	: $(BONUS_OBJ)
	$(AR) $(NAME) $(BONUS_OBJ)

%.o 	: %.c libft.h
		$(CC) $(CFLAGS) -c $< -o $@

clean 	:
		$(RM) $(ALL)

fclean 	: clean
		$(RM) $(NAME)

re		: fclean all

.PHONY	: all bonus clean fclean re