CC				= cc
CFLAGS_BASE		= -Wall -Werror -Wextra -Iinclude -g -Wshadow -Wpedantic
CFLAGS_BASE		+= -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter
CFLAGS			= $(CFLAGS_BASE)
XFLAGS			= -lX11 -lXext -lm -lz -lXfixes
MAKEFLAGS		+= --no-print-directory -s
AR				= ar -src
RM				= rm -f
MKDIR			= mkdir -p

BIN_DIR			= bin
BIN				= $(BIN_DIR)/cub3d
BIN_SAN			= $(BIN_DIR)/cub3d_san
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
RED				= \033[0;31m
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

# Normal run without memory checks
run:	all
		printf "$(GREEN)Running normal binary$(RESET)\n"
		./$(BIN) ./maps/large_map.cub

# Run with Valgrind for thorough memory leak checking
mleak:	all
		printf "$(YELLOW)Running with Valgrind leak checker$(RESET)\n"
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(BIN) ./maps/large_map.cub

# Run with Address Sanitizer
san:
		$(RM) -r $(BIN_DIR)/$(BIN_SAN)
		printf "⚙️  $(BLUE)Building with Address Sanitizer$(RESET)\n"
		@$(MKDIR) $(BIN_DIR)
		printf "⚙️  $(BLUE)Building LIB_FT$(RESET)\n"
		make all -C $(LIBFT_DIR)
		printf "⚙️  $(BLUE)Building MINILIBX$(RESET)\n"
		make all -C $(MINILIBX_DIR) > /dev/null
		printf "⚙️  $(BLUE)Compiling with sanitizer flags$(RESET)\n"
		$(CC) $(CFLAGS_BASE) -fsanitize=address,leak $(SRCS) -o $(BIN_SAN) -I$(LIBFT_DIR)/include $(XFLAGS) $(LIBFT) $(MINILIBX)
		printf "☑️ $(GREEN)Sanitized binary compiled in$(RESET): $(BIN_SAN)\n"
		printf "$(RED)Running with Address Sanitizer$(RESET)\n"
		ASAN_OPTIONS=symbolize=1:detect_leaks=1:abort_on_error=1:verbose=1  ./$(BIN_SAN)

debug:	all
		$(CC) $(CFLAGS) $(XFLAGS) $(NAME) $(LIBFT) $(MINILIBX) -g3 -o a.out

.SILENT:	all clean fclean re
.PHONY:		all clean fclean re run mleak san debug
