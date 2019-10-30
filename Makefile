NAME=rtv1

SRCS=	rtv1.c \
		scene_parser.c \
		checkers.c \
		error_handling.c

OBJS=$(SRCS:.c=.o)

LIBS_DIR=libs
OBJS_DIR=build
SRCS_DIR=srcs
OBJS_PATH=$(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH=$(addprefix $(SRCS_DIR)/, $(SRCS))
INCLUDES=includes

FLAGS= #-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_PATH) $(INCLUDES)/rtv1.h
	make -C $(LIBS_DIR)/centropy
	gcc $(OBJS_PATH) -I$(INCLUDES) -I$(LIBS_DIR)/centropy/includes -I$(LIBS_DIR)/simplist/includes $(LIBS_DIR)/*/*.a -o $(NAME) -lmlx -framework openGL -framework AppKit

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) -I$(INCLUDES) -I$(LIBS_DIR)/centropy/includes -I$(LIBS_DIR)/simplist/includes -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	make -C $(LIBS_DIR)/centropy clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBS_DIR)/centropy fclean
	rm -rf $(NAME)

re: fclean all
