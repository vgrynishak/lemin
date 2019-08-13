#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/26 13:54:22 by vgrynish          #+#    #+#              #
#    Updated: 2018/12/08 21:08:38 by vgrynish         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

FLAGS  += -Wall -Werror -Wextra
FLAGS  += -I incl/
OBJ_D = obj
S_D = src

SRC = 	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
    	ft_memchr.c ft_memcmp.c \
	ft_strlen.c ft_abs.c\
	ft_strdup.c ft_strcpy.c ft_strncpy.c \
	ft_strcat.c ft_strncat.c \
	ft_strlcat.c \
	ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
	ft_strcmp.c ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
 	ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c \
	ft_strsplit.c \
	ft_strtrim.c \
	ft_itoa.c \
	\
	ft_putchar.c ft_putchar_fd.c \
	ft_putstr.c ft_putstr_fd.c \
	ft_putendl.c ft_putendl_fd.c \
	ft_putnbr.c ft_putnbr_fd.c \
	\
	ft_lstnew.c \
	ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_striteri.c \
	ft_lstmap.c ft_strmapi.c \
	ft_define.c \
	ft_printf.c \
	is_type.c \
	robota_with_csvp.c \
	robota_with_diu.c \
	robota_with_f.c \
	robota_with_ox.c \
	unicod_union.c \
	work_with_size.c \
	ft_lstnum.c\
	get_next_line.c 
		
OBJ = $(addprefix $(OBJ_D)/, $(patsubst %.c,%.o,$(SRC)))


all: $(NAME)

$(OBJ_D):
	@mkdir -p obj

$(OBJ_D)/%.o: $(S_D)/%.c | $(OBJ_D)
	@gcc -c $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
clean:
	 @/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME) $(OBJ_D)

re: fclean all