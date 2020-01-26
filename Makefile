# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: merras <merras@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/22 20:55:47 by aait-el-          #+#    #+#              #
#    Updated: 2020/01/25 22:18:43 by merras           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRCS =	vec1.c \
		vec2.c \
		rotation.c \
		rtv1.c \
		scene_parser.c \
		initial_parsing_utilities.c \
		properties_scene_parsing_utilities.c \
		checkers.c \
		renderer.c \
		hit.c \
		intersections.c \
		color_picker.c 

OBJS = $(SRCS:.c=.o)

LIBS_DIR = libs
OBJS_DIR = build
SRCS_DIR = srcs
MLX = -I ./minilibx_macos -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
INCLUDES = includes libs/centropy/includes libs/simplist/includes

FLAGS = -g -Wall -Werror -Wextra
INCLUDES_FLAG = $(addprefix -I, $(INCLUDES))

all: $(NAME)

$(NAME): $(OBJS_PATH)
	make -C $(LIBS_DIR)/centropy
	make -C $(LIBS_DIR)/simplist
	gcc $(OBJS_PATH) $(INCLUDES_FLAG) $(MLX) $(LIBS_DIR)/*/*.a -o $(NAME) -lmlx -framework openGL -framework AppKit

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) $(INCLUDES_FLAG) -c $< -o $@

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
