cmake_minimum_required(VERSION 3.0.2)

project(game LANGUAGES CXX)
set(GAME_NAME myawesomegame)

option(RELEASE_BUILD "Release build" OFF)

if (RELEASE_BUILD)
    message("== Release BUILD ==")
    set(GAME_RESOURCES_FOLDER "/usr/games/${GAME_NAME}-resources")
else()
    message("== Debug BUILD ==")
    set(GAME_RESOURCES_FOLDER "game")
endif()

set(GAME_ASSETS_FOLDER "${GAME_RESOURCES_FOLDER}/assets")

# Set directory folders
set (PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/game/include")
set (PROJECT_SRC_DIR     "${PROJECT_SOURCE_DIR}/game/src")
set (PROJECT_ASSETS_DIR  "${PROJECT_SOURCE_DIR}/game/assets")

# Gets the list of files inside the src directory
file(GLOB_RECURSE SOURCES "${PROJECT_SRC_DIR}/*.cpp"
                          "${PROJECT_SRC_DIR}/*.c")

configure_file("${PROJECT_INCLUDE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")

# Include Headers
include_directories(${PROJECT_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")


#### Compilation ####
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilation Flags
set(COMPILE_FLAGS "")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -std=c++11 -Wshadow -O2 -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -std=c++11 -Wshadow -O2 -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} /Wall")
endif()

# Cmake compilation flags redefinition
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")



#### Dependencies ####

# Add engine
set (PROJECT_ENGINE_DIR "${PROJECT_SOURCE_DIR}/game/engine")
add_subdirectory(${PROJECT_ENGINE_DIR})
include_directories(${ENGINE_INCLUDE_DIR})


#### Executable ####

add_executable(${GAME_NAME} ${SOURCES})
target_link_libraries(${GAME_NAME}
                      engine
                      SDL2 SDL2_image SDL2_ttf SDL2_mixer)


#### Custom Commands ####

# Copy assets folder to build
add_custom_command(TARGET ${GAME_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_ASSETS_DIR} "${CMAKE_BINARY_DIR}/${GAME_ASSETS_FOLDER}")


#### Instalation ####
install(TARGETS ${GAME_NAME} DESTINATION /usr/games)
install(DIRECTORY ${PROJECT_ASSETS_DIR} DESTINATION ${GAME_RESOURCES_FOLDER})

#### Packs ####

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME                ${GAME_NAME})
set(CPACK_PACKAGE_VENDOR              "UnB - FGA")
set(CPACK_RESOURCE_FILE_LICENSE       "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR       "1")
set(CPACK_PACKAGE_VERSION_MINOR       "0")
set(CPACK_PACKAGE_CONTACT             "Matheus Faria <matheusfaria@unb.br>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Base game project of IJE")
set(CPACK_PACKAGE_DESCRIPTION         "Base game project of IJE with all the contents that a game needs to be developed on the course")
set(CPACK_PACKAGE_URL                 "https://unbgames.github.io")

# .deb related info
set(CPACK_DEBIAN_FILE_NAME            "DEB-DEFAULT")
set(CPACK_DEBIAN_PACKAGE_SECTION      "Games")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE     ${CPACK_PACKAGE_URL})
set(CPACK_DEBIAN_PACKAGE_DEPENDS      "libsdl2-2.0-0, libsdl2-image-2.0-0, libsdl2-mixer-2.0-0, libsdl2-ttf-2.0-0")

# .rpm related info
set(CPACK_RPM_FILE_NAME        "RPM-DEFAULT")
set(CPACK_RPM_PACKAGE_LICENSE  "MIT")
set(CPACK_RPM_PACKAGE_URL      ${CPACK_PACKAGE_URL})
set(CPACK_RPM_PACKAGE_REQUIRES "SDL2, SDL2_image, SDL2_mixer, SDL2_ttf")
include (CPack)
