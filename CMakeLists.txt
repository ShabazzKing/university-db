cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        main # release-1.10.0
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

project(university-db)
# enable_testing()

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} src/main.cpp src/Database.cpp src/Student.cpp)
# add_executable(${PROJECT_NAME}-ut test.cpp advancedCalculator.cpp)

# target_link_libraries(${PROJECT_NAME}-ut gtest_main)

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME}-ut)
