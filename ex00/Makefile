.SILENT:
.PHONY:	all init clean fclean re test FORCE

include config.mk
include bitcoin_exchange.mk

OBJS := $(patsubst $(SRCSDIR)%.cpp, $(OBJS_DIR)%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): Makefile $(OBJS) | $(EXEC_DIR)
	echo "$(PURPLE)Compiling $(NAME) in progress...$(RESET)"
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
	echo "$(GREEN)$(EXEC) completed successfully!$(RESET)"

	echo "$(GREEN)"
	echo "┌───────────────────────────────────────────────────────────┐"
	echo "│      Compilation finished successfully! ᕕ(⌐■_■)ᕗ ♪♬       │"
	echo "└───────────────────────────────────────────────────────────┘"

	echo "$(GREEN) $(NAME) is now ready to run ／人◕ ‿‿ ◕人＼ "
	echo "$(RESET)"


$(OBJS_DIR)%.o: $(SRCSDIR)%.cpp Makefile config.mk bitcoin_exchange.mk | $(OBJS_DIR)
	mkdir -p $(dir $@)
	echo "$(PURPLE)Compiling $<...$(RESET)"
	$(CXX) $(CXXFLAGS) -c -o $@ $<	
	echo "$(GREEN)$< completed successfully!$(RESET)"

$(OBJS_DIR):
	echo "$(YELLOW)Creating directory $(OBJS_DIR)...$(RESET)"
		
		mkdir -p $(OBJS_DIR)

$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR) directory...$(RESET)"

		mkdir -p $(EXEC_DIR)

clean:
	$(RM_DIR) $(OBJS_DIR)
	echo "$(RED)Cleaning of .o and .d files completed successfully! ／人◕ ‿‿ ◕人＼$(RESET)"

fclean: clean
	$(RM_DIR) $(EXEC_DIR)
	echo "$(GREEN)"
	echo "┌──────────────────────────────────────────────────────────┐"
	echo "│      Deletion finished successfully! ( ◔ ω ◔) ノシ       │"
	echo "└──────────────────────────────────────────────────────────┘"
	echo "                           ╱|、"
	echo "                         (˚ˎ 。7"
	echo "                          |、˜|"
	echo "                         じしˍ,)ノ"
	echo "$(RESET)"

re: fclean all

FORCE:

-include $(DEPS)