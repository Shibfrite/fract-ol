# ==========================
# Project Name
# ==========================
NAME		:= fract-ol

# ==========================
# Compiler and Flags
# ==========================
CC		  := gcc
CFLAGS	  := -Wall -Wextra -Werror -g

# ==========================
# Directory Paths
# ==========================
INC_DIR	 	:= includes
SRC_DIR	 	:= srcs
OBJ_DIR	 	:= objs
LIBFT_DIR	:= libft

# ==========================
# Source Files
# ==========================
SRC_FILES   := main.c input.c fractal_utils.c fractal_render.c 

# Add prefixes for each directory to the respective files
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# ==========================
# Object Files
# ==========================
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ==========================
# Include Paths
# ==========================
INC			:= -I$(INC_DIR) -Iminilibx-linux -I$(LIBFT_DIR)/includes
MLX	 		:= -Lminilibx-linux -lmlx -lXext -lX11 -lm
LIBFT		:= $(LIBFT_DIR)/libft.a

# ==========================
# Directories to Create
# ==========================
DIRS		:= $(INC_DIR) $(SRC_DIR) $(OBJ_DIR) $(LIBFT_DIR)

# ==========================
# Default Target
# ==========================
all: $(NAME)

# ==========================
# Build the Executable
# ==========================
$(NAME): $(OBJS) $(LIBFT)
	echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $@
	echo "$(NAME) created successfully!"

# ==========================
# Compile Source Files to Object Files
# ==========================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ==========================
# Rule to Compile libft
# ==========================
$(LIBFT):
	@echo "Compiling libft..."
	$(MAKE) -C $(LIBFT_DIR) -s
	@echo "libft compiled successfully."

# ==========================
# Create Directories
# ==========================
$(DIRS):
	mkdir -p $@
	echo "Created directory: $@"

# ==========================
# Clean Object Files and Directories
# ==========================
clean:
	echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) -s clean
	echo "Object files cleaned."

# ==========================
# Clean Executable Files
# ==========================
fclean: clean
	echo "Cleaning executable..."
	rm -f $(NAME)
	echo "Executable cleaned."

# ==========================
# Rebuild Everything from Scratch
# ==========================
re: fclean all

.SILENT:
.PHONY: all clean fclean re
