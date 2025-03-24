# Include the colors for better visualization
include make/colors.mk

# ---- Paths ----
PRINTF_DIR  = ..
TESTER_DIR  = .
SRC_DIR     = $(TESTER_DIR)/srcs
TEST_DIR    = $(SRC_DIR)/tests
OBJ_DIR     = $(TESTER_DIR)/objs
BIN_DIR     = $(TESTER_DIR)/bin
PROG_DIR    = $(TESTER_DIR)/program/tests
INC_DIR     = $(TESTER_DIR)/includes
UTILS_DIR   = $(TESTER_DIR)/utils
STRESS_DIR  = $(UTILS_DIR)/stress
LIB_DIR     = $(TESTER_DIR)/lib

# ---- Files ----
# Libraries
LIBFTPRINTF       = $(PRINTF_DIR)/libftprintf.a
LIBTESTER         = $(LIB_DIR)/libft_printf_tester.a

# Add verification utility - include it in the utility files instead of building separately
VERIFY_SRC = $(UTILS_DIR)/verify_library.c
# No separate executable needed

# Utils source files - include verify_library.c in the utility sources
UTILS_SRCS        = $(filter-out $(UTILS_DIR)/ft_printf_test_utils.c, $(wildcard $(UTILS_DIR)/*.c))
STRESS_SRCS       = $(wildcard $(STRESS_DIR)/*.c)
ALL_UTILS_SRCS    = $(UTILS_SRCS) $(STRESS_SRCS)

# Utils object files
UTILS_OBJS        = $(patsubst $(UTILS_DIR)/%.c, $(OBJ_DIR)/utils/%.o, $(UTILS_SRCS))
STRESS_OBJS       = $(patsubst $(STRESS_DIR)/%.c, $(OBJ_DIR)/utils/stress/%.o, $(STRESS_SRCS))
ALL_UTILS_OBJS    = $(UTILS_OBJS) $(STRESS_OBJS)

# Source files for all tests
MANDATORY_TEST_SRC = $(TEST_DIR)/ft_printf_mandatory_test.c
BONUS_TEST_SRCS    = $(wildcard $(TEST_DIR)/bonus_*.c)
CONTROLLER_SRC     = $(SRC_DIR)/ft_printf_ultimate_controller.c

# Files that are utilities, not standalone programs (should be compiled to objects only)
UTIL_TEST_SRCS     = 

# All other test programs (excluding utility files and already categorized files)
OTHER_TEST_SRCS    = $(filter-out $(BONUS_TEST_SRCS) $(MANDATORY_TEST_SRC), $(wildcard $(TEST_DIR)/*.c))
ALL_TEST_SRCS      = $(MANDATORY_TEST_SRC) $(OTHER_TEST_SRCS) $(BONUS_TEST_SRCS)

# Object files
MANDATORY_TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(MANDATORY_TEST_SRC))
BONUS_TEST_OBJS    = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(BONUS_TEST_SRCS))
OTHER_TEST_OBJS    = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(OTHER_TEST_SRCS))
UTIL_TEST_OBJS     = $(patsubst $(UTILS_DIR)/%.c, $(OBJ_DIR)/utils/%.o, $(UTIL_TEST_SRCS))  # Updated pattern
ALL_TEST_OBJS      = $(MANDATORY_TEST_OBJ) $(OTHER_TEST_OBJS) $(BONUS_TEST_OBJS) $(UTIL_TEST_OBJS)
CONTROLLER_OBJ     = $(OBJ_DIR)/ft_printf_ultimate_controller.o

# Executables
MANDATORY_TEST_EXEC = $(PROG_DIR)/ft_printf_mandatory_test
BONUS_TEST_EXECS    = $(patsubst $(TEST_DIR)/%.c, $(PROG_DIR)/%, $(BONUS_TEST_SRCS))
OTHER_TEST_EXECS    = $(patsubst $(TEST_DIR)/%.c, $(PROG_DIR)/%, $(OTHER_TEST_SRCS))
ALL_TEST_EXECS      = $(MANDATORY_TEST_EXEC) $(OTHER_TEST_EXECS) $(BONUS_TEST_EXECS)
CONTROLLER_EXEC     = $(BIN_DIR)/ft_printf_ultimate_controller
CONTROLLER_BONUS_EXEC = $(BIN_DIR)/ft_printf_ultimate_controller_bonus

# ---- Compiler Options ----
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror
INCLUDES  = -I$(INC_DIR) -I$(PRINTF_DIR) -I$(UTILS_DIR) -I$(STRESS_DIR) -I$(TEST_DIR) -I$(TESTER_DIR)/headers

# ---- Make Rules ----
all: setup $(LIBFTPRINTF) $(LIBTESTER) $(MANDATORY_TEST_EXEC) $(OTHER_TEST_EXECS) $(CONTROLLER_EXEC)
	@$(call section_header, "Mandatory Tests Built Successfully")

# Completely separate bonus target that uses the bonus library for everything
bonus: setup
	@$(call section_header, "Building Bonus Tests")
	@$(MAKE) -C $(PRINTF_DIR) bonus
	@$(call pulse_status, "Completed", "libftprintf.a with bonus features")
	@$(MAKE) $(LIBTESTER)
	@$(MAKE) USING_BONUS=1 ensure_testers
	@$(MAKE) USING_BONUS=1 $(CONTROLLER_BONUS_EXEC)
	@$(call section_header, "Bonus Tests Built Successfully")

# Comprehensive target that builds everything
all_tests: all bonus
	@$(call section_header, "All Tests - Including Bonus - Built Successfully")

# Create necessary directories
setup:
	@mkdir -p $(OBJ_DIR)/utils/stress $(OBJ_DIR)/tests $(BIN_DIR) $(PROG_DIR) $(LIB_DIR)
	@$(call pulse_status, "Setting up", "directories created")

# Build the main printf library
$(LIBFTPRINTF):
	@$(call section_header, "Building ft_printf Mandatory Library")
	@$(MAKE) -C $(PRINTF_DIR)
	@$(call pulse_status, "Completed", "libftprintf.a ready")

# Build the tester library from utils and stress testing files - now also include test utilities
$(LIBTESTER): $(ALL_UTILS_OBJS) $(UTIL_TEST_OBJS)
	@$(call section_header, "Building Tester Library")
	@ar rcs $@ $^
	@$(call pulse_status, "Completed", "libft_printf_tester.a ready")

# Compile all test programs
ensure_testers: setup 
	@$(MAKE) $(ALL_TEST_EXECS)
	@$(call pulse_status, "Test Programs", "compiled successfully")

# Compile controller program (mandatory version)
$(CONTROLLER_EXEC): $(CONTROLLER_SRC) $(LIBFTPRINTF) $(LIBTESTER)
	@$(call pulse_status, "Compiling", "ultimate controller - mandatory")
	@$(CC) $(CFLAGS) $(INCLUDES) $(CONTROLLER_SRC) -o $@ -L$(LIB_DIR) -lft_printf_tester -L$(PRINTF_DIR) -lftprintf

# Compile controller program (bonus version)
$(CONTROLLER_BONUS_EXEC): $(CONTROLLER_SRC) $(LIBFTPRINTF) $(LIBTESTER)
	@$(call pulse_status, "Compiling", "ultimate controller - bonus")
	@$(CC) $(CFLAGS) $(INCLUDES) -DUSE_BONUS_LIB $(CONTROLLER_SRC) -o $@ -L$(LIB_DIR) -lft_printf_tester -L$(PRINTF_DIR) -lftprintf
	@$(call pulse_status, "Compiled", "$@")

# Compile controller object if needed
$(CONTROLLER_OBJ): $(CONTROLLER_SRC)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "${BUILD_ICON} ${SUBTLE}Compiled: ${ACCENT1}$<${RST}\n"

# Compile mandatory test program
$(MANDATORY_TEST_EXEC): $(MANDATORY_TEST_SRC) $(LIBFTPRINTF) $(LIBTESTER)
	@mkdir -p $(PROG_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ -L$(LIB_DIR) -lft_printf_tester -L$(PRINTF_DIR) -lftprintf
	@$(call pulse_status, "Compiled", "$@")

# Compile test programs - uses conditional linking based on USING_BONUS variable
$(PROG_DIR)/%: $(TEST_DIR)/%.c $(LIBTESTER)
	@mkdir -p $(PROG_DIR)
	@if [ "$(USING_BONUS)" = "1" ]; then \
		$(MAKE) -C $(PRINTF_DIR) bonus; \
		$(CC) $(CFLAGS) $(INCLUDES) -DUSE_BONUS_LIB $< -o $@ -L$(LIB_DIR) -lft_printf_tester -L$(PRINTF_DIR) -lftprintf; \
	else \
		$(MAKE) -C $(PRINTF_DIR); \
		$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ -L$(LIB_DIR) -lft_printf_tester -L$(PRINTF_DIR) -lftprintf; \
	fi
	@$(call pulse_status, "Compiled", "$@")

# Compile utils object files
$(OBJ_DIR)/utils/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "${BUILD_ICON} ${SUBTLE}Compiled: ${ACCENT1}$<${RST}\n"

# Compile stress utils object files
$(OBJ_DIR)/utils/stress/%.o: $(STRESS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "${BUILD_ICON} ${SUBTLE}Compiled: ${ACCENT1}$<${RST}\n"

# Compile test object files
$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "${BUILD_ICON} ${SUBTLE}Compiled: ${ACCENT1}$<${RST}\n"

# Run the test suite
run: all
	@$(call print_banner)
	@$(CONTROLLER_EXEC)

# Run the bonus test suite
run_bonus: bonus
	@$(call print_banner)
	@$(CONTROLLER_BONUS_EXEC) --bonus

# Run all tests (both mandatory and bonus)
run_all: all_tests
	@$(call print_banner)
	@$(CONTROLLER_EXEC)
	@echo "=== Running bonus tests ==="
	@$(CONTROLLER_BONUS_EXEC) --bonus

# Force a complete rebuild of the project
purge: fclean
	@rm -f $(PRINTF_DIR)/*.a
	@rm -rf $(PRINTF_DIR)/objs
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(call pulse_status, "Purged", "all libraries and object files")

# New rebuild targets that ensure complete rebuilds
rebuild_mandatory: purge
	@$(MAKE) all
	@$(call pulse_status, "Rebuilt", "mandatory version from scratch")

rebuild_bonus: purge
	@$(MAKE) bonus
	@$(call pulse_status, "Rebuilt", "bonus version from scratch")

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(call pulse_status, "Cleaned", "object files removed")

# Clean everything
fclean: clean
	@rm -rf $(BIN_DIR) $(PROG_DIR) $(LIB_DIR)
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(call pulse_status, "Full Clean", "all generated files removed")

# Rebuild everything
re: fclean all
	@$(call pulse_status, "Rebuilt", "project from scratch")

# Display help
help:
	@$(call show_help)

.PHONY: all bonus all_tests setup purge rebuild_mandatory rebuild_bonus ensure_testers run run_bonus run_all clean fclean re help