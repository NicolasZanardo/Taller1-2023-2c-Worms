#===============================================================================
add_subdirectory(poc_sdl)
#===============================================================================
include_directories(PUBLIC ${SDL2PP_INCLUDE_DIRS})
file(COPY resources/sprites DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(GLOB_RECURSE model_sources src/model/*.cpp src/model/*.h)
file(GLOB_RECURSE presentation_sources src/presentation/*.cpp src/presentation/*.h)

add_library(client
        ${model_sources}
        ${presentation_sources}
        src/client.cpp src/client.h
)

add_executable(client_app
        src/client_main.cpp
)

target_include_directories(client_app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/model")
target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/presentation")

target_link_libraries(client_app
        PRIVATE common
        PUBLIC ${SDL2PP_LIBRARIES}
        PUBLIC client
)
