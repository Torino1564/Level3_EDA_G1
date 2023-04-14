cmake_minimum_required(VERSION 3.1.4)
project(main VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

# From "Working with CMake" documentation:
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # AddressSanitizer (ASan)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # UndefinedBehaviorSanitizer (UBSan)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

add_executable(main main.cpp Corazones.cpp CSVData.cpp)

# nlohmann-json
find_package(nlohmann_json CONFIG REQUIRED)
target_include_directories(main PRIVATE ${nlohmann_json_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${nlohmann_json_LIBRARIES})

# nlohmann-json
find_package(raylib CONFIG REQUIRED)
target_include_directories(main PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${raylib_LIBRARIES})


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # From "Working with CMake" documentation:
    target_link_libraries(main PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(main PRIVATE m ${CMAKE_DL_LIBS} pthread GL rt X11)
endif()

# Test
#enable_testing()

#add_executable(main_test main_test.cpp)

#add_test(NAME test1 COMMAND main_test)
