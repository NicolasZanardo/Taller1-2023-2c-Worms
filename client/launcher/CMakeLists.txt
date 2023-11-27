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
