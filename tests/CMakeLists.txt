# === Helper Function to Create Test Executables ===

# This function abstracts the creation of test executables.
# Usage: create_test(test_name)
# It assumes a file named <test_name>.cpp exists in the same directory.
function(create_test filename)
    # Define the test executable name based on the filename
    set(TEST_EXECUTABLE ${filename})

    # Create the executable target using the given test file
    add_executable(${TEST_EXECUTABLE} ${filename}.cpp)

    # Set C++ standard requirements for this test target
    set_target_properties(${TEST_EXECUTABLE} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    # Include paths to allow non-relative includes like "rotations.hpp" and "json.hpp"
    target_include_directories(${TEST_EXECUTABLE} PRIVATE
        ${CMAKE_SOURCE_DIR}/include   # Project headers
        ${CMAKE_SOURCE_DIR}/lib       # Third-party or local libs
    )
endfunction()

# === Test Targets ===

# Declare individual test targets using the helper function above
# This will create a test executable for `rotations_test.cpp`
create_test(rotations_test)
