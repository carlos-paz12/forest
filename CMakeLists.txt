# === Project Metadata ===

# Application name (used as the project name and executable name)
set(APP_NAME "forest")

# Application version
set(APP_VERSION 1.0)

# Short description of the project
set(APP_DESCRIPTION "Implementation of the AVL and Red-Black trees.")

# Programming language used in the project (C++ in this case)
set(APP_LANG CXX)

# Minimum required CMake version
set(CMAKE_VERSION 3.22.1)

# === Declare the project ===

# Specify the minimum CMake version required to build this project
cmake_minimum_required(VERSION ${CMAKE_VERSION})

# Declare the project using the variables defined above
project(${APP_NAME}
    VERSION ${APP_VERSION}
    DESCRIPTION "${APP_DESCRIPTION}"
    LANGUAGES ${APP_LANG}
)

# === Output & Tooling Options ===

# Set where the compiled binary (executable) will be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Export compile_commands.json (helps editors like VS Code with IntelliSense via clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# === Main Executable ===

# Define the executable target and its entry point source file
add_executable(${APP_NAME} src/main.cpp)

# Specify directories to search for header files.
# These paths are added to the compiler's -I flags, so you can use non-relative includes like:
#    #include "rotations.hpp" or #include "nlohmann/json.hpp"
target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include   # For your project's headers
    ${CMAKE_CURRENT_SOURCE_DIR}/lib       # For third-party headers like nlohmann/json
)

# === Compilation Properties ===

# Require C++17 standard
set_target_properties(${APP_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Add compiler flags for strict warnings and good coding practices
target_compile_options(${APP_NAME} PRIVATE
    -Wall        # Show all common warnings
    -Wextra      # Show extra (less common) warnings
    -Wpedantic   # Enforce ISO compliance
    # -O2        # Optimization flag (commented for debug, useful for release)
)

# === Testing ===

# Optional: Variable used by the tests subdirectory
set(TEST_DRIVER test_driver)

# Add the subdirectory that contains the test configuration and test sources
add_subdirectory(tests)
