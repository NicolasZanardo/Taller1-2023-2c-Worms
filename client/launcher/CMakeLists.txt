#===============================================================================
# Lobby del Cliente por Consola.
# add_executable(client_console_lobby
#     main_console_lobby.cpp
#     client_lobby.cpp client_lobby.h
#     client_lobby_settings.cpp client_lobby_settings.h
#     lobby_parser.cpp lobby_parser.h    
# )

# target_link_libraries(client_console_lobby PUBLIC common)

#===============================================================================
set(PROJECT_SOURCES
        main.cpp
        launcher.cpp
        launcher.h
        launcher.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(launcher_worms
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(launcher_worms
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(launcher_worms PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


# # Run the uic tool manually to generate the corresponding C++ code from the .ui file
# set(UI_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/launcher.h)
# add_custom_command(
#     OUTPUT ${UI_HEADERS}
#     COMMAND ${Qt5Widgets_UIC_EXECUTABLE} launcher.ui -o ${UI_HEADERS}
#     DEPENDS launcher.ui
#     COMMENT "Running UIC on ${UI_HEADERS}"
# )

# # Include the generated header file in the target sources
# target_sources(launcher_worms PRIVATE ${UI_HEADERS})

# # Link the necessary Qt modules
# target_link_libraries(launcher_worms PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
