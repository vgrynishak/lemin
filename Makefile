CC	=	gcc
CFLAGS	=	##-Wall -Wextra -Werror

NAME	=	lem-in
LIBFT	=	libft/libft.a

INC	=
SRC	=	main.c option.c action/action.c parse/parce.c parse/save_room.c parse/save_neighbors.c algoritm/algoritm.c algoritm/prepare_to_split.c algoritm/prepare_to_merge.c algoritm/find_one_path.c input/input.c input/find_line.c input/show_input.c input/helper_input.c input/helper_solution.c
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


