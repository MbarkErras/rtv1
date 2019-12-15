NAME=rtv1

SRCS=	_dev_.c \
		rtv1.c \
		scene_parser.c \
		initial_parsing_utilities.c \
		properties_scene_parsing_utilities.c \
		error_handling.c \
		checkers.c \
		t_object.c \
		renderer.c \
		draw.c\
		vec1.c\
		vec2.c\
		vec3.c

OBJS=$(SRCS:.c=.o)

LIBS_DIR=libs
OBJS_DIR=build
SRCS_DIR=srcs
MLX = -I ./minilibx_macos -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit
OBJS_PATH=$(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH=$(addprefix $(SRCS_DIR)/, $(SRCS))
INCLUDES=includes

FLAGS= -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_PATH) $(INCLUDES)/rtv1.h
	make -C $(LIBS_DIR)/centropy
	make -C $(LIBS_DIR)/simplist
	gcc $(OBJS_PATH) -I$(INCLUDES) -I$(LIBS_DIR)/centropy/includes -I$(LIBS_DIR)/simplist/includes $(MLX) $(LIBS_DIR)/*/*.a -o $(NAME) -lmlx -framework openGL -framework AppKit

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) -I$(INCLUDES) -I$(LIBS_DIR)/centropy/includes -I$(LIBS_DIR)/simplist/includes -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	make -C $(LIBS_DIR)/centropy clean
	make -C $(LIBS_DIR)/simplist clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBS_DIR)/centropy fclean
	make -C $(LIBS_DIR)/simplist fclean
	rm -rf $(NAME)

re: fclean all
