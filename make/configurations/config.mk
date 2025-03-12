

# Base configuration settings
# (Any shared settings across the project)

# Directory structure validation
$(shell mkdir -p $(OBJ_DIR) $(PROGRAM_DIR))

# Enable all test targets by default
ENABLE_ALL_TESTS = 1

# Toggle verbose output (set to 1 for more details)
VERBOSE = 0

# Default timestamp format
TIMESTAMP_FORMAT = "%Y-%m-%d %H:%M:%S"
