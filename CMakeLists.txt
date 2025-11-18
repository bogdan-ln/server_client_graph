cmake_minimum_required(VERSION 3.20)
project(GraphProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройки для SFML
set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/sfml@2/2.6.2_1")
find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

# Настройки для Boost через find_package
include_directories(
    include
    /opt/homebrew/Cellar/boost@1.85/1.85.0_3/include
)

link_directories(/opt/homebrew/Cellar/boost@1.85/1.85.0_3/lib)

# Общие include директории
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Добавляем поддиректории
add_subdirectory(main)