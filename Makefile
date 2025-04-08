CC				= cc
CFLAGS			= -Wall -Werror -Wextra -Iinclude
XFLAGS			= -lX11 -lXext -lm -lz
MAKEFLAGS		+= --no-print-directory -s
AR				= ar -src
RM				= rm -f
MKDIR			= mkdir -p

BIN_DIR			= bin
BIN				= $(BIN_DIR)/cub3d
NAME			= lib/cub3d.a
SRC_DIR			= src
OBJ_DIR			= obj

SRCS			= $(shell find $(SRC_DIR) -name '*.c')
OBJS			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT_DIR		= lib/libft
LIBFT			= $(LIBFT_DIR)/libft.a
MINILIBX_DIR	= lib/minilibx/
MINILIBX		= $(MINILIBX_DIR)libmlx.a

GREEN  			= \033[0;32m
YELLOW 			= \033[1;33m
BLUE   			= \033[1;34m
RED    			= \033[0;31m
RESET  			= \033[0m

all:	$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
		@$(MKDIR) $(dir $@)
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):	$(OBJS)
		@$(MKDIR) $(BIN_DIR)
		printf "⚙️  $(BLUE)Building LIB_FT$(RESET)\n"
		make all -C $(LIBFT_DIR)
		printf "⚙️  $(BLUE)Building MINILIBX$(RESET)\n"
		make all -C $(MINILIBX_DIR) > /dev/null
		printf "⚙️  $(BLUE)Building CUB3D$(RESET)\n"
		$(AR) $@ $(OBJS)
		$(CC) $(CFLAGS) $(XFLAGS) $@ $(LIBFT) $(MINILIBX) -o $(BIN)
		printf "☑️ $(GREEN)Compiled in$(RESET): $(BIN)\n"

clean:
		$(RM) -r $(OBJ_DIR)
		$(RM) a.out
		printf "🧹 $(RED)Cleaning$(RESET): $(OBJ_DIR)\n"

fclean:	clean
		$(RM) -r $(BIN_DIR)
		$(RM) $(NAME)
		make fclean -C $(LIBFT_DIR)
		printf "🧹 $(RED)Cleaning$(RESET): $(LIBFT_DIR)\n"

re:		fclean all run

run:	all
		./$(BIN)

debug:	all
		$(CC) $(CFLAGS) $(XFLAGS) $(NAME) $(LIBFT) $(MINILIBX) -g3 -o a.out

mleak:	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN)


.SILENT:	all clean fclean re
.PHONY:		all clean fclean re run
