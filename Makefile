# Exec #
NAME			=	Webserv

# PATH #
SRCS_DIR		=	srcs
OBJS_DIR		=	objs
INCS_DIR		=	includes
LIBF_DIR		=	libft-cpp
VPATH			=	$(SRCS_DIR):$(OBJS_DIR):$(INCS_DIR):$(LIBF_DIR)

# File with Path #
SRCS_PATH		=	$(wildcard $(SRCS_DIR)/*.cpp)
OBJS_PATH		=	$(patsubst $(SRCS_DIR)%,$(OBJS_DIR)%,$(SRCS_PATH:%.cpp=%.o))
INCS_PATH		=	$(wildcard $(INCS_DIR)/*.hpp)

# File #
SRCS			=	$(notdir $(SRCS_PATH))
OBJS			=	$(notdir $(OBJS_PATH))
INCS			=	$(notdir $(INCS_PATH))

# Compile #
CC				=	clang++
CFLAGS			=	#-Wall -Wextra -Werror
CVERSION		=	--std=c++98
FSANITIZE		=	-fsanitize=address
LFLAGS  		=	-I $(INCS_DIR) -I$(LIBF_DIR)
CALLF			=	$(CC) $(CFLAGS) $(CVERSION)
CALLFLIB		=	$(CC) $(CFLAGS) $(CVERSION) $(LFLAGS) $(FSANITIZE)

# Defauilt Make #
all				:	directories lib $(NAME)

# Stuff #
$(NAME)			:	$(OBJS_PATH) $(LIBF_DIR)/libft.a
	$(CALLFLIB) $(OBJS_PATH) -o $(NAME) $(LIBF_DIR)/libft.a

$(OBJS_DIR)/%.o	:	%.cpp $(INCS)
	$(CALLFLIB) -c $< -o $@

# Make the Directories #
directories		:
	@mkdir -p $(OBJS_DIR)

lib:
	make -C $(LIBF_DIR)

run: all
	./$(NAME)

# Clean obj #
clean			:
	@rm -f $(OBJS_PATH)
	@rm -rf $(NAME).dSYM
	@make clean -C $(LIBF_DIR)
	$(info Build done! Cleaning object files...)

# Clean all #
fclean			:	clean
	@rm -rf $(OBJS_DIR)
	@rm -f $(NAME)
	@make fclean -C $(LIBF_DIR)
	$(info Build done! Cleaning $(NAME) exec...)

re				:	fclean all

.PHONY			:	all fclean clean re directories run