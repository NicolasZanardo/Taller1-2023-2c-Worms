#===============================================================================
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable (sdlpp-events
  example_sdl_events.cpp
  Player.cpp
  Animation.cpp
)

target_link_libraries(sdlpp-events ${SDL2PP_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
