CC	=	gcc
CFLAGS	=	##-Wall -Wextra -Werror

NAME	=	lem-in
LIBFT	=	libft/libft.a

INC	=
SRC	=	main.c lists/action.c parse/parce.c parse/save_room.c parse/save_neighbors.c algoritm/algoritm.c algoritm/prepare_to_split.c algoritm/prepare_to_merge.c algoritm/find_one_path.c input/input.c input/find_line.c input/show_input.c
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


