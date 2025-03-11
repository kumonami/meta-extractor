cmake_minimum_required(VERSION 3.10)
project(metadata_extractor)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

add_executable(metadata_extractor
    main.cpp
    mainwindow.cpp
    src/extractor.cpp
    src/utils.cpp
    src/cleaner.cpp
    src/geo.cpp
    mainwindow.hpp
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PKG_CONFIG_PATH /opt/homebrew/Cellar/libexif/0.6.25/lib/pkgconfig)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEXIF REQUIRED libexif)

if(LIBEXIF_FOUND)
    message(STATUS "libexif found: ${LIBEXIF_LIBRARIES}")
else()
    message(FATAL_ERROR "libexif not found!")
endif()

target_include_directories(metadata_extractor PRIVATE ${LIBEXIF_INCLUDE_DIRS})
target_link_directories(metadata_extractor PRIVATE ${LIBEXIF_LIBRARY_DIRS})
target_link_libraries(metadata_extractor PRIVATE ${LIBEXIF_LIBRARIES})

find_package(CURL REQUIRED)

if(CURL_FOUND)
    message(STATUS "libcurl found: ${CURL_LIBRARIES}")
else()
    message(FATAL_ERROR "libcurl not found!")
endif()

include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(metadata_extractor PRIVATE ${CURL_LIBRARIES})
target_link_libraries(metadata_extractor PRIVATE Qt6::Widgets)

include_directories(/opt/homebrew/include)