CC	=	gcc
CFLAGS	=	#-Wall -Wextra -Werror

NAME	=	lem-in
LIBFT	=	libft/libft.a

INC	=
SRC	=	main.c lists/action.c parse/parce.c algoritm/algoritm.c input/input.c input/find_line.c input/show_input.c
OBJ	=	$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

$(LIBFT):
	make -sC libft/

clean:
	rm -f $(OBJ)
	make clean -sC libft/

fclean: clean
	rm -f $(NAME)
	make fclean -sC libft/

re: fclean all

%.o: %.c lemin.h
	$(CC) $(CFLAGS) -c $< -I libft/incl -I . -o $@


