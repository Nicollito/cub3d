.PHONY : all check-build real-all debug clean fclean re

MAKEFLAGS += --no-print-directory

NAME = cub3D
CC = cc
CFLAGS = -Werror -Wextra -Wall
CFLAGS += 										\
					-Ilibft						\
					-Iinclude/error				\
					-Iinclude/cube				\
					-Iinclude/init				\
					-Iinclude/parsing
DFLAGS = -MMD -MF
LIB = libft/libft.a
#------------------------------------DEBUG------------------------------------#
CFLAGS_DEBUG = -g3 -Wuninitialized -fno-inline -O0
DEBUG_MODE =
#-------------------------------------SRC-------------------------------------#
SRC 			= 										\
						src
SRC_DIR 		=										\
						error							\
						init							\
						main							\
						parsing
error_SRCS		=										\
						error.c
init_SRCS		=										\
						gnl.c							\
						init.c
main_SRCS		=										\
						main.c
parsing_SRCS	=										\
						parsing.c
SRCS =	$(foreach dir,$(SRC_DIR), $(addprefix $(SRC)/$(dir)/,$($(dir)_SRCS)))
#-----------------------------------OBJECTS-----------------------------------#
OBJ_DIR = 											\
					obj
OBJS = $(patsubst $(SRC)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
#-------------------------------------DEPS------------------------------------#
DEPS_DIR = deps
DEPS = $(patsubst $(SRC)/%.c, $(DEPS_DIR)/%.d, $(SRCS))
#-----------------------------------INCLUDE-----------------------------------#
INCLUDE				= 								\
						include
HEADER_DIR			=								\
						cube						\
						error						\
						parsing
cube_HDR			= 								\
						cube.h
error_HDR			=								\
						error.h
parsing_HDR			=								\
						parsing.h
HEADER = 	$(foreach dir,$(HEADER_DIR), $(addprefix $(INCLUDE)/$(dir)/,$($(dir)_HDR)))
#------------------------------------UTILS------------------------------------#
SRCS_LIB = $(shell make -s -C libft print_src)
HEADER_LIB = $(shell make -s -C libft print_header)
#------------------------------------RULES------------------------------------#
all : $(LIB) check-build

print_header :
	@echo $(HEADER)

check-build :
	@if [ -f "$(NAME)" ] \
		&& [ -z "$$(find "$(OBJ_DIR)" -type f -newer "$(NAME)")" ] \
		&& [ -z "$$(find libft \( -name "*.c" -o -name "*.h" -o -name "Makefile" \) -newer "$(LIB)")" ] \
		&& [ -z "$$(find "$(SRC)" -name "*.c" -newer "$(NAME)")" ] \
		&& [ -z "$$(find "$(INCLUDE)" -name "*.h" -newer "$(NAME)")" ] \
		&& [ -z "$$(find "$(LIB)" -type f -newer "$(NAME)")" ] \
		&& [ -z "$$(find . -name "Makefile" -newer "$(NAME)")" ]; then \
		echo "✅ Project is already up to date!"; \
	else \
		$(MAKE) real-all; \
	fi

real-all : $(LIB) $(OBJS) $(NAME) $(HEADER)

$(OBJ_DIR)/%.o : $(SRC)/%.c Makefile
	@mkdir -p $(dir $@) $(dir $(DEPS))
	@$(CC) $(CFLAGS) $(DFLAGS) $(DEPS_DIR)/$*.d -c $< -o $@
	

$(NAME) : $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(LFLAGS)
	@echo "🚀 Executable is ready to run."

$(LIB) : $(addprefix libft/, $(SRCS_LIB) $(HEADER_LIB)) libft/Makefile
	@echo "📦 Building libft..."
	@$(MAKE) -C libft

-include $(DEPS)

debug :
	@echo "🎯 Compiling for debug: $(CFLAGS) $(CFLAGS_DEBUG)"
	@$(MAKE) debug -C libft
	@$(MAKE) re CFLAGS="$(CFLAGS) $(CFLAGS_DEBUG)" DEBUG_MODE=debug

clean :
	@rm -rf $(OBJ_DIR) $(DEPS_DIR)
	@echo "🧹 Object files removed."

fclean : clean
ifndef DEBUG_MODE
	@$(MAKE) fclean -C libft
endif
	@rm -rf $(NAME)
	@echo "🧼 Full clean complete."

re : fclean all